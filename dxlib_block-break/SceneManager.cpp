#include "SceneManager.h"
#include "Scene.h"
#include <Windows.h>

#include "DxLib.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

Scene* SceneManager::s_activeScene = nullptr;
Scene* SceneManager::s_nextScene = nullptr;
std::vector<SceneBuild> SceneManager::s_sceneBuilds;

//シーンとシーンコンストラクタとの紐づけ
class SceneBuild {
private:
	std::string m_sceneName;
	std::function<Scene* ()> m_factory;
public:
	SceneBuild(const std::string& sceneName, std::function<Scene* ()>& factory)
		:m_sceneName(sceneName), m_factory(factory)
	{
	}
	const std::string& GetSceneName()const { return m_sceneName; }
	Scene* CreateScene()const { return m_factory(); }
};

void SceneManager::RegisterSceneBuild(const std::string& sceneName, std::function<Scene*()> factory)
{
	s_sceneBuilds.emplace_back(sceneName, factory);
}

bool SceneManager::LoadScene(const std::string& sceneName)
{
	//シーンのビルド番号を取得
	int index = GetBuildIndexByName(sceneName);
	if (index < 0)
	{
		MessageBox(nullptr, "無効なビルド番号が返されたため、シーンが読み込めませんでした。", "Error", MB_OK);
		return false;
	}
	//シーンのインスタンスを作成
	Scene* scene = s_sceneBuilds[index].CreateScene();
	scene->SetName(sceneName);

	//作成したシーンを次のシーンに設定
	s_nextScene = scene;

	return true;
}

bool SceneManager::LoadScene(int buildIndex)
{
	if (s_nextScene != nullptr) 
	{
		MessageBox(nullptr, "既に読み込み待ちのシーンがあるため、シーンが読み込めませんでした。", "Error", MB_OK);
		return false;
	}

	if ((buildIndex < 0) || (s_sceneBuilds.size() <= buildIndex))
	{
		MessageBox(nullptr, "無効なビルド番号が返されたため、シーンが読み込めませんでした。", "Error", MB_OK);
		return false;
	}

	//シーンのインスタンスを作成
	Scene* scene = s_sceneBuilds[buildIndex].CreateScene();
	scene->SetName(s_sceneBuilds[buildIndex].GetSceneName());

	//作成したシーンを次のシーンに設定
	s_nextScene = scene;

	return true;
}

int SceneManager::GetBuildIndexByName(const std::string& sceneName)
{
	int size = (int)s_sceneBuilds.size();
	for (int i = 0; i < size; i++)
	{
		if (sceneName == s_sceneBuilds[i].GetSceneName())
			return i;
	}
	return -1;
}

void SceneManager::Update()
{
	//次のシーンの読み込み待ち状態なら、
	if (s_nextScene != nullptr) 
	{
		//スクリーンをクリア
		ClearDrawScreen();
		//TODO:NowLoading... 描画
		//m_nowLoadingTxt->Render();
		//裏画面の内容を表画面に反映させる
		ScreenFlip();

		//前のシーンの終了処理
		Release(s_activeScene);

		//次のシーンを稼働中のシーンとして設定
		s_activeScene = s_nextScene;
		s_nextScene = nullptr;

		//シーン開始時処理
		s_activeScene->Start();
	}
	//シーンの更新処理
	s_activeScene->Update();
}

void SceneManager::Render()
{
	//シーン描画
	s_activeScene->Render();
}

void SceneManager::Fin() 
{
	Release(s_activeScene);
	Release(s_nextScene);
	
	//Release(s_nowLoadingTxt);
}
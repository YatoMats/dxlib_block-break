#include "SceneManager.h"
#include "Scene.h"
#include <Windows.h>
#include "DxLib.h"
#include <future>

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

Scene* SceneManager::s_activeScene = nullptr;
Scene* SceneManager::s_nextScene = nullptr;
std::vector<SceneBuild> SceneManager::s_sceneBuilds;

bool SceneManager::s_isNowLoading = false;
bool SceneManager::s_isLoaded = false;

//�V�[���ƃV�[���R���X�g���N�^�Ƃ̕R�Â�
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
	if (s_nextScene != nullptr)
	{
		MessageBox(nullptr, "���ɓǂݍ��ݑ҂��̃V�[�������邽�߁A�V�[�����ǂݍ��߂܂���ł����B", "Error", MB_OK);
		return false;
	}

	//�V�[���̃r���h�ԍ����擾
	int index = GetBuildIndexByName(sceneName);
	if (index < 0)
	{
		MessageBox(nullptr, "�����ȃr���h�ԍ����Ԃ��ꂽ���߁A�V�[�����ǂݍ��߂܂���ł����B", "Error", MB_OK);
		return false;
	}
	//�V�[���̃C���X�^���X���쐬
	Scene* scene = s_sceneBuilds[index].CreateScene();
	scene->SetName(sceneName);

	//�쐬�����V�[�������̃V�[���ɐݒ�
	s_nextScene = scene;

	return true;
}

bool SceneManager::LoadScene(int buildIndex)
{
	if (s_nextScene != nullptr) 
	{
		MessageBox(nullptr, "���ɓǂݍ��ݑ҂��̃V�[�������邽�߁A�V�[�����ǂݍ��߂܂���ł����B", "Error", MB_OK);
		return false;
	}
	if ((buildIndex < 0) || (s_sceneBuilds.size() <= buildIndex))
	{
		MessageBox(nullptr, "�����ȃr���h�ԍ����Ԃ��ꂽ���߁A�V�[�����ǂݍ��߂܂���ł����B", "Error", MB_OK);
		return false;
	}

	//�V�[���̃C���X�^���X���쐬
	Scene* scene = s_sceneBuilds[buildIndex].CreateScene();
	scene->SetName(s_sceneBuilds[buildIndex].GetSceneName());

	//�쐬�����V�[�������̃V�[���ɐݒ�
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

bool SceneManager::LoadSceneAsync(const std::string& sceneName)
{
	//�񓯊��V�[���ǂݍ��݃t���O�𗧂Ă�
	s_isNowLoading = true;

	//�V�[���C���X�^���X�̍쐬
	if (LoadScene(sceneName)) {
		//�V�[���̓ǂݍ��݊֐���񓯊��Ŏ��s
		auto result = std::async(std::launch::async, [=]() { s_nextScene->Start(); s_isLoaded = true; });
		return true;
	}

	return false;
}

void SceneManager::Update()
{
	//���̃V�[���̓ǂݍ��ݑ҂���ԂȂ�A
	if (s_nextScene != nullptr) 
	{
		//�񓯊��̃V�[���ǂݍ��݂Ȃ�A
		if (s_isNowLoading) 
		{
			//�ǂݍ��݊������Ă�����A
			if (s_isLoaded) 
			{
				s_isNowLoading = false;
				s_isLoaded = false;

				//�O�̃V�[���̏I������
				Release(s_activeScene);
				//�ǂݍ��񂾃V�[�����ғ����̃V�[���Ƃ��Đݒ�
				s_activeScene = s_nextScene;
				s_nextScene = nullptr;
			}
		}
		else 
		{
			//�X�N���[�����N���A
			ClearDrawScreen();

			//TODO:NowLoading... �`��
			//m_nowLoadingTxt->Render();

			//����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();

			//�O�̃V�[���̏I������
			Release(s_activeScene);

			//���̃V�[�����ғ����̃V�[���Ƃ��Đݒ�
			s_activeScene = s_nextScene;
			s_nextScene = nullptr;

			//�V�[���J�n������
			s_activeScene->Start();
		}
	}

	//�V�[���̍X�V����
	s_activeScene->Update();
}

void SceneManager::Render()
{
	//�V�[���`��
	s_activeScene->Render();
}

void SceneManager::Fin() 
{
	Release(s_activeScene);
	Release(s_nextScene);
	
	//Release(s_nowLoadingTxt);
}
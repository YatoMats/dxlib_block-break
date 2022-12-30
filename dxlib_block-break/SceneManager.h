#pragma once
#include <string>
#include <functional>
#include <vector>

class Scene;
class SceneBuild;

class SceneManager {
	//現在稼働中のシーン
	static Scene* s_activeScene;
	//次に読み込むシーン
	static Scene* s_nextScene;
	//シーンビルド設定
	static std::vector<SceneBuild> s_sceneBuilds;
public:
	//シーンのビルド設定を登録(シーン名とシーンコンストラクタとを紐づけ)
	static void RegisterSceneBuild(const std::string& sceneName, std::function<Scene*()> factory);

	//シーンの読み込み
	static bool LoadScene(const std::string& sceneName);
	//シーンのビルド番号から、シーンを読み込み
	static bool LoadScene(int buildIndex);

	//現在稼働中のシーンを取得
	static Scene* GetActiveScene() { return s_activeScene; }
private:
	//シーン名から、シーンのビルド番号を取得
	static int GetBuildIndexByName(const std::string& sceneName);
public:	//後でprivateに。 (main-loop直下以外からの呼び出しを防ぐ)
	static void Update();
	static void Render();
	static void Fin();
};
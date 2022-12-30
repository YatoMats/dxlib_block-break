#pragma once
#include <string>
#include <functional>
#include <vector>

class Scene;
class SceneBuild;

class SceneManager {
	//���݉ғ����̃V�[��
	static Scene* s_activeScene;
	//���ɓǂݍ��ރV�[��
	static Scene* s_nextScene;
	//�V�[���r���h�ݒ�
	static std::vector<SceneBuild> s_sceneBuilds;
public:
	//�V�[���̃r���h�ݒ��o�^(�V�[�����ƃV�[���R���X�g���N�^�Ƃ�R�Â�)
	static void RegisterSceneBuild(const std::string& sceneName, std::function<Scene*()> factory);

	//�V�[���̓ǂݍ���
	static bool LoadScene(const std::string& sceneName);
	//�V�[���̃r���h�ԍ�����A�V�[����ǂݍ���
	static bool LoadScene(int buildIndex);

	//���݉ғ����̃V�[�����擾
	static Scene* GetActiveScene() { return s_activeScene; }
private:
	//�V�[��������A�V�[���̃r���h�ԍ����擾
	static int GetBuildIndexByName(const std::string& sceneName);
public:	//���private�ɁB (main-loop�����ȊO����̌Ăяo����h��)
	static void Update();
	static void Render();
	static void Fin();
};
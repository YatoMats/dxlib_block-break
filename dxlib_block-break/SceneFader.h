#pragma once
#include <string>

class Image;

class SceneFader {
protected:
	//�t�F�[�h�p�p�l���摜
	Image* m_panel;
	//�p�l�������x
	float m_alpha;

	//�t�F�[�h�����܂ł̍Œ�҂�����
	float m_waitTime = 0.1f;//0.25f;
	//�҂����Ԍv���p
	float m_timer = 0.0f;

public:
	SceneFader();
	virtual ~SceneFader();

	virtual void Update(){}
	virtual void Render();
};

//���̃V�[���֑J�ڂ���ۂ̃t�F�[�h�A�E�g����
class SceneFadeOuter :public SceneFader 
{
	//���ɓǂݍ��ރV�[����
	std::string m_nextSceneName;

	//�񓯊��œǂݍ��ނ��ǂ���
	bool m_useAsync = true;

	bool m_isTriggered = false;
public:
	SceneFadeOuter();

	void Update()override;

	//�ǂݍ��݊J�n�̃t���O�𗧂Ă�
	void SetTrigger(const std::string& nextSceneName) { 
		m_isTriggered = true; m_nextSceneName = nextSceneName; 
	}
};

//�V�[���J�n���̃t�F�[�h�C������
class SceneFadeInner : public SceneFader 
{
	//�V�[���t�F�[�h�������t���O
	bool m_isDone = false;
public:
	SceneFadeInner();

	void Update()override;
	void Render()override;
};
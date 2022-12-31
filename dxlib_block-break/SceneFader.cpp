#include "SceneFader.h"
#include "App.h"
#include "Image.h"
#include "SceneManager.h"

SceneFader::SceneFader()
	:m_panel(new Image("")), m_alpha(0.0f)
{
	//�t�F�[�h�p�̃p�l���F
	m_panel->SetColor(0.5f, 0.5f, 0.5f);
}

SceneFader::~SceneFader()
{
	delete m_panel;
	m_panel = nullptr;
}

void SceneFader::Render()
{
	//�E�B���h�E�𑜓x
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//�V�[���t�F�[�h�p�p�l���`��
	m_panel->Render(0, 0, scrw, scrh);
}


SceneFadeOuter::SceneFadeOuter()
{
	//�ŏ��͓�����
	m_panel->alpha = 0.0f;
}

void SceneFadeOuter::Update()
{
	if (!m_isTriggered) return;

	//���Ԍv��
	m_timer += 1.0f / App::GetFrameRate();
	if (m_timer > m_waitTime) {
		m_timer = 0.0f;

		//���ԂɂȂ�����A���̃V�[���ǂݍ���
		if (m_useAsync)
			SceneManager::LoadSceneAsync(m_nextSceneName);
		else 
			SceneManager::LoadScene(m_nextSceneName);
	}
	//���X�Ƀp�l����s������
	m_panel->alpha += m_timer / m_waitTime;
}


SceneFadeInner::SceneFadeInner()
{
	//�ŏ��͕s������
	m_panel->alpha = 1.0f;
}

void SceneFadeInner::Update()
{
	//���Ԍv��
	m_timer += 1.0f / App::GetFrameRate();
	if (m_timer > m_waitTime) {
		m_timer = 0.0f;

		//���ԂɂȂ�����A�����t���O�𗧂Ă�
		m_isDone = true;
	}
	//���X�Ƀp�l���̂𓧖���
	m_panel->alpha -= m_timer / m_waitTime;
}

void SceneFadeInner::Render()
{
	if (m_isDone) return;

	//�E�B���h�E�𑜓x
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//�V�[���t�F�[�h�p�p�l���`��
	m_panel->Render(0, 0, scrw, scrh);
}

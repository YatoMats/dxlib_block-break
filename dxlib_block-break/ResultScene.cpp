#include "ResultScene.h"
#include "DataManager.h"
#include "SceneFader.h"

#ifndef Release
#define	Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

void ResultScene::Start()
{
	//�V�[���t�F�[�h�p�I�u�W�F�N�g�쐬
	m_sceneFadeInner = new SceneFadeInner();
	m_sceneFadeOuter = new SceneFadeOuter();

	m_sceneFadeSE = new Audio("assets/aud/se/decision3.mp3");
	m_sceneFadeSE->volume = 1.0f;


	//�W���t�H���g�T�C�Y�ݒ�
	Text::SetDefaultFontSize(28);


	//�w�i�摜�ǂݍ���
	m_bgImg = new Image("assets/img/cosmos.png");
	m_bgImg->alpha = 0.7f;


	//�^�C�g���e�L�X�g�쐬
	m_titleTxt = new Text("GAME CLEAR!");
	m_titleTxt->SetColor(1, 1, 0);
	m_titleTxt->ChangeFontSize(44);

	//�������e�L�X�g�쐬
	m_descTxt = new Text("Press any Button to ReStart..");
	m_descTxt->SetColor(0, 1, 0);


	//���U���g�f�[�^�̎󂯎��
	ResultData dat = DataManager::GetResultData();

	//�Q�[�����s�Ȃ�A
	if (!dat.isSuccess)
	{
		//�^�C�g���e�L�X�g�����s���e�L�X�g�ɏ�������
		m_titleTxt->SetText("GAME OVER...");
		m_titleTxt->SetColor(1, 0, 1);
		//���s��BGM�ǂݍ���
		m_bgm = new Audio("assets/aud/bgm/sad_bgm.mp3");
		m_bgm->volume = 0.3f;
		m_bgm->Play();

		return;
	}
	else {
		//������BGM�ǂݍ���
		m_bgm = new Audio("assets/aud/bgm/rpg_victory.mp3");
		m_bgm->volume = 0.3f;
	}

	//���U���g�f�[�^������e�L�X�g�ɒǉ���������
	std::string descStr = "";
	descStr += "SCORE:" + std::to_string(dat.score) + " \n";
	descStr += "HP:" + std::to_string(dat.hp) + " \n";

	//���b�ϊ�
	int sec = dat.time % 60;
	int min = dat.time / 60 % 60;
	//������ϊ�
	std::string minStr = std::to_string(min);
	std::string secStr = std::to_string(sec);
	//�[������
	if (sec < 10) secStr = "0" + secStr;
	if (min < 10) minStr = "0" + minStr;
	//���ԕ\���p�e�L�X�g�ɐݒ�
	std::string timeStr = "ClearTime " + minStr + ":" + secStr;
	descStr += timeStr;

	//�����e�L�X�g�ɏ�L�������ǉ�.
	m_descTxt->SetText(m_descTxt->GetText() + " \n\n" + descStr);

	//BGM�Đ�
	m_bgm->isLooping = true;
	m_bgm->volume = 0.3f;
	m_bgm->Play();
}

ResultScene::~ResultScene()
{
	//���������
	Release(m_bgImg);

	Release(m_titleTxt);
	Release(m_descTxt);
	Release(m_scoreTxt);

	Release(m_sceneFadeInner);
	Release(m_sceneFadeOuter);
	Release(m_sceneFadeSE);

	Release(m_bgm);
}

void ResultScene::Update()
{
	if (InputManager::GetKeyEnter(KEY_ID::ESC)) { }

	//��L�ȊO�́A�����ꂩ�̃L�[�������ꂽ��A
	else if (InputManager::GetAnyKeyEnter()) 
	{
		//SE�Đ�
		m_sceneFadeSE->Play();

		//���C���V�[���֖߂�
		m_sceneFadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
	}

	//�V�[���t�F�[�h�X�V����
	m_sceneFadeInner->Update();
	m_sceneFadeOuter->Update();
}

void ResultScene::Render()
{
	//�X�N���[��������
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//�w�i�摜�`��
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//�^�C�g���e�L�X�g�`��
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 150);

	//�������e�L�X�g�`��
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(scrw / 2 - dw / 2, scrh / 2);

	//�V�[���t�F�[�h�p�p�l���`��
	m_sceneFadeInner->Render();
	m_sceneFadeOuter->Render();
}

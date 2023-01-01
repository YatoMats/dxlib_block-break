#include "TitleScene.h"
#include <Windows.h>
#include "Camera.h"
#include "Button.h"
#include "SceneFader.h"

#include "DataManager.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

//TODO:Config
	//BGM,SE���ʐݒ�
	//KeyConfig
	//��ʃT�C�Y

void TitleScene::Start()
{
	//�X�N���[��������
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//�f�t�H���g�̃t�H���g�T�C�Y���w��
	Text::SetDefaultFontSize(28);

	//BGM�Đ�
	m_bgm = new Audio("assets/aud/bgm/newworld.mp3");
	m_bgm->volume = 0.33f;
	m_bgm->isLooping = true;
	m_bgm->Play();

	//�w�i�摜�ǂݍ���
	m_bgImg = new Image("assets/img/cosmos.png");
	m_bgImg->alpha = 0.7f;

	//�^�C�g���e�L�X�g�쐬
	m_titleTxt = new Text("BLOCK BREAKOUT");
	m_titleTxt->SetColor(0.9f, 1, 0);
	m_titleTxt->ChangeFontSize(60);
	//�t�H���g���A�����T�C�Y�A���������̐ݒ�
	//m_titleTxt->CreateTextFont("�l�r ����", 60);


	//�������e�L�X�g�쐬
	m_descTxt = new Text("Press Any Button ...");
	m_descTxt->SetColor(0, 1, 0);
	//�t�H���g���A�����T�C�Y�A���������̐ݒ�
	m_descTxt->CreateTextFont("���C���I", 28);

	//�{�^���쐬
	/*Image* btnImg = new Image("");
	Text* btnTxt = new Text("Button");
	btnTxt->SetColor(0.2f, 0.2f, 0.2f);
	m_button = new Button(
		btnImg, btnTxt,
		scrw - 150 - 25, scrh - 50 - 25,
		150, 50
	);
	//�{�^������������
	m_button->SetOnClick([=]() {
		//m_button->SetText(new Text("Clicked!"));
		SceneManager::LoadScene("MainScene"); 
		});*/

	//�V�[���t�F�[�h�C���p�I�u�W�F�N�g�쐬
	m_sceneFadeInner = new SceneFadeInner();
	m_sceneFadeOuter = new SceneFadeOuter();

	//�V�[���t�F�[�h�A�E�g��SE
	m_fadeOutSE = new Audio("assets/aud/se/decision3.mp3");
	m_fadeOutSE->volume = 1.0f;
}

TitleScene::~TitleScene()
{
	//���������
	Release(m_bgm);
	Release(m_bgImg);

	Release(m_titleTxt);
	Release(m_descTxt);

	Release(m_button);

	Release(m_sceneFadeInner);
	Release(m_sceneFadeOuter);
	Release(m_fadeOutSE);
}

void TitleScene::Update()
{
	//�{�^���X�V����
	//m_button->Update();

	if (//InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT) ||
		//InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE) ||
		//InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT) ||
		InputManager::GetKeyEnter(KEY_ID::ESC)
		)
	{
	}
	//��L�ȊO�́A�����ꂩ�̃L�[�������ꂽ��A�܂��A�V�[�������ɓǂݍ��ݒ��łȂ��Ȃ�A
	else if (InputManager::GetAnyKeyEnter() && !SceneManager::IsNowLoading())
	{
		//SE�Đ�
		m_fadeOutSE->Play();

		//���C���V�[����ǂݍ���
		m_sceneFadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadSceneAsync("MainScene");
	}

	//�V�[���t�F�[�h�p�l���X�V����
	m_sceneFadeInner->Update();
	m_sceneFadeOuter->Update();
}

void TitleScene::Render()
{
	//�X�N���[���������擾
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//�w�i�摜�`��
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//�^�C�g���e�L�X�g�`��
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 200);

	//�������e�L�X�g�`��
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(scrw / 2 - dw / 2, scrh - 200);

	//�{�^���`��
	//m_button->Render();

	//�V�[���t�F�[�h�p�l���`��
	m_sceneFadeInner->Render();
	m_sceneFadeOuter->Render();
}

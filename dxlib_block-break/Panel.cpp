#include "Panel.h"
#include "Image.h"
#include "Text.h"
#include "Button.h"
#include "App.h"
#include "InputManager.h"
#include "Audio.h"
#include "SceneFader.h"
#include "SceneManager.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

Panel::Panel()
{
	//�`��̈敝����
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();


	//�p�l���摜
	m_img = new Image("");
	m_img->alpha = 0.93f;
	m_img->SetColor(0.8f, 0.8f, 0.8f);


	//�p�l���^�C�g���e�L�X�g
	m_titleTxt = new Text("PAUSE");
	m_titleTxt->SetColor(1.0f, 0.0f, 1.0f);
	m_titleTxt->ChangeFontSize(48);


	//�p�l����������e�L�X�g
	m_descTxt = new Text(
		"Press any Key to Back to the Game..."
	);
	m_descTxt->SetColor(0.2f, 0.2f, 0.2f);
	m_descTxt->ChangeFontSize(24);


	//�p�l���{�^��������SE�ǂݍ���
	m_decisionSE = new Audio("assets/aud/se/decision3.mp3");
	m_decisionSE->volume = 1.0f;


	//�V�[���t�F�[�h�p�I�u�W�F�N�g�쐬
	m_fadeOuter = new SceneFadeOuter();


	//�p�l���{�^���T�C�Y
	int btnw = 200;
	int btnh = 50;

	//�^�C�g���ցA�p�l���{�^���ݒ�
	Text* toTitleTxt = new Text("�^�C�g����");
	toTitleTxt->ChangeFontSize(24);
	toTitleTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button0 = new Button(new Image(""), toTitleTxt,
		25, (int)scrh - btnh - 100,
		btnw, btnh);

	//�{�^���N���b�N���A
	m_button0->SetOnClick([=]() {
		//�V�[���t�F�[�h�A�E�g��SE�Đ�
		m_decisionSE->Play();
		//�^�C�g���V�[���֑J��
		//m_fadeOuter->SetTrigger("TitleScene");
		//SceneManager::LoadScene("TitleScene");
		});


	//�Q�[���֖߂�A�p�l���{�^���ݒ�
	Text* toGameTxt = new Text("�Q�[���֖߂�");
	toGameTxt->ChangeFontSize(24);
	toGameTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button1 = new Button(new Image(""), toGameTxt,
		(int)scrw / 2 - btnw / 2, (int)scrh - btnh - 100,
		btnw, btnh);
	m_button1->SetOnClick([=]() {
		isActive = !isActive;
		});


	//���߂���A�p�l���{�^���ݒ�
	Text* reTxt = new Text("���߂���");
	reTxt->ChangeFontSize(24);
	reTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button2 = new Button(new Image(""), reTxt,
		(int)scrw - btnw - 25, (int)scrh - btnh - 100,
		btnw, btnh);
	m_button2->SetOnClick([=]() {
		//�V�[���t�F�[�h�A�E�g��SE�Đ�
		m_decisionSE->Play();
		//���C���V�[���֑J��
		//m_fadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
		});
}

Panel::~Panel()
{
	//���������
	Release(m_img);
	Release(m_titleTxt);

	Release(m_descTxt);

	Release(m_button0);
	Release(m_button1);
	Release(m_button2);

	Release(m_decisionSE);
	Release(m_fadeOuter);
}

void Panel::Update()
{
	//�p�l���A�N�e�B�u���A
	if (isActive) {
		//�{�^���X�V����
		m_button0->Update();
		m_button1->Update();
		m_button2->Update();
	}
}

void Panel::Render()
{
	//�A�N�e�B�u���̂݁A�`��
	if (!isActive) return;

	//�`��̈敝����
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//�p�l���摜�`��
	m_img->Render(0, 0, scrw, scrh);

	//�p�l�����o�������`��
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 100);

	//�p�l�������e�L�X�g�`��
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(100, 300);

	//�{�^���`��
	m_button0->Render();
	m_button1->Render();
	m_button2->Render();
}

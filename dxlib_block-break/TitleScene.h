#pragma once
#include "Scene.h"

class Button;

class SceneFadeInner;
class SceneFadeOuter;

class TitleScene : public Scene {
	//�^�C�g���e�L�X�g
	Text* m_titleTxt;
	//��������e�L�X�g
	Text* m_descTxt;
	//�w�i�摜
	Image* m_bgImg;
	//BGM
	Audio* m_bgm;

	//�{�^��
	Button* m_button;

	//�V�[���t�F�[�h�p
	SceneFadeInner* m_sceneFadeInner;
	SceneFadeOuter* m_sceneFadeOuter;

	//�V�[���t�F�[�h�A�E�g��SE
	Audio* m_fadeOutSE;
public:
	~TitleScene();
	void Start()override;
	void Update()override;
	void Render()override;
};
#pragma once
#include "Scene.h"

class ResultData;
class SceneFadeOuter;
class SceneFadeInner;

class ResultScene :public Scene {
	//�w�i�摜
	Image* m_bgImg;

	//�p�l���^�C�g���e�L�X�g
	Text* m_titleTxt;
	//�������e�L�X�g
	Text* m_descTxt;

	//�X�R�A�\���p�e�L�X�g
	Text* m_scoreTxt;

	//BGM
	Audio* m_bgm;

	//�V�[���t�F�[�h�p
	SceneFadeInner* m_sceneFadeInner;
	SceneFadeOuter* m_sceneFadeOuter;

	//�V�[���t�F�[�h��SE
	Audio* m_sceneFadeSE;

public:
	~ResultScene();
	void Start()override;
	void Update()override;
	void Render()override;
};
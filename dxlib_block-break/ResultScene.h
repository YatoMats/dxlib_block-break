#pragma once
#include "Scene.h"

class ResultData;
class SceneFadeOuter;
class SceneFadeInner;

class ResultScene :public Scene {
	//背景画像
	Image* m_bgImg;

	//パネルタイトルテキスト
	Text* m_titleTxt;
	//説明文テキスト
	Text* m_descTxt;

	//スコア表示用テキスト
	Text* m_scoreTxt;

	//BGM
	Audio* m_bgm;

	//シーンフェード用
	SceneFadeInner* m_sceneFadeInner;
	SceneFadeOuter* m_sceneFadeOuter;

	//シーンフェード時SE
	Audio* m_sceneFadeSE;

public:
	~ResultScene();
	void Start()override;
	void Update()override;
	void Render()override;
};
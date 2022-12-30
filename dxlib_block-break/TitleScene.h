#pragma once
#include "Scene.h"

class Button;

class SceneFadeInner;
class SceneFadeOuter;

class TitleScene : public Scene {
	//タイトルテキスト
	Text* m_titleTxt;
	//操作説明テキスト
	Text* m_descTxt;
	//背景画像
	Image* m_bgImg;
	//BGM
	Audio* m_bgm;

	//ボタン
	Button* m_button;

	//シーンフェード用
	SceneFadeInner* m_sceneFadeInner;
	SceneFadeOuter* m_sceneFadeOuter;

	//シーンフェードアウト時SE
	Audio* m_fadeOutSE;
public:
	~TitleScene();
	void Start()override;
	void Update()override;
	void Render()override;
};
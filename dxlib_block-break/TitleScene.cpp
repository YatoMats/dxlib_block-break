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
	//BGM,SE音量設定
	//KeyConfig
	//画面サイズ

void TitleScene::Start()
{
	//スクリーン幅高さ
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//デフォルトのフォントサイズを指定
	Text::SetDefaultFontSize(28);

	//BGM再生
	m_bgm = new Audio("assets/aud/bgm/newworld.mp3");
	m_bgm->volume = 0.33f;
	m_bgm->isLooping = true;
	m_bgm->Play();

	//背景画像読み込み
	m_bgImg = new Image("assets/img/cosmos.png");
	m_bgImg->alpha = 0.7f;

	//タイトルテキスト作成
	m_titleTxt = new Text("BLOCK BREAKOUT");
	m_titleTxt->SetColor(0.9f, 1, 0);
	m_titleTxt->ChangeFontSize(60);
	//フォント名、文字サイズ、文字太さの設定
	//m_titleTxt->CreateTextFont("ＭＳ 明朝", 60);


	//説明文テキスト作成
	m_descTxt = new Text("Press Any Button ...");
	m_descTxt->SetColor(0, 1, 0);
	//フォント名、文字サイズ、文字太さの設定
	m_descTxt->CreateTextFont("メイリオ", 28);

	//ボタン作成
	/*Image* btnImg = new Image("");
	Text* btnTxt = new Text("Button");
	btnTxt->SetColor(0.2f, 0.2f, 0.2f);
	m_button = new Button(
		btnImg, btnTxt,
		scrw - 150 - 25, scrh - 50 - 25,
		150, 50
	);
	//ボタン押下時処理
	m_button->SetOnClick([=]() {
		//m_button->SetText(new Text("Clicked!"));
		SceneManager::LoadScene("MainScene"); 
		});*/

	//シーンフェードイン用オブジェクト作成
	m_sceneFadeInner = new SceneFadeInner();
	m_sceneFadeOuter = new SceneFadeOuter();

	//シーンフェードアウト時SE
	m_fadeOutSE = new Audio("assets/aud/se/decision3.mp3");
	m_fadeOutSE->volume = 1.0f;
}

TitleScene::~TitleScene()
{
	//メモリ解放
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
	//ボタン更新処理
	//m_button->Update();

	if (//InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT) ||
		//InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE) ||
		//InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT) ||
		InputManager::GetKeyEnter(KEY_ID::ESC)
		)
	{
	}
	//上記以外の、いずれかのキーが押されたら、また、シーンを既に読み込み中でないなら、
	else if (InputManager::GetAnyKeyEnter() && !SceneManager::IsNowLoading())
	{
		//SE再生
		m_fadeOutSE->Play();

		//メインシーンを読み込む
		m_sceneFadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadSceneAsync("MainScene");
	}

	//シーンフェードパネル更新処理
	m_sceneFadeInner->Update();
	m_sceneFadeOuter->Update();
}

void TitleScene::Render()
{
	//スクリーン幅高さ取得
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();
	
	//背景画像描画
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//タイトルテキスト描画
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 200);

	//説明文テキスト描画
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(scrw / 2 - dw / 2, scrh - 200);

	//ボタン描画
	//m_button->Render();

	//シーンフェードパネル描画
	m_sceneFadeInner->Render();
	m_sceneFadeOuter->Render();
}

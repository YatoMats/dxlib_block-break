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
	//描画領域幅高さ
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();


	//パネル画像
	m_img = new Image("");
	m_img->alpha = 0.93f;
	m_img->SetColor(0.8f, 0.8f, 0.8f);


	//パネルタイトルテキスト
	m_titleTxt = new Text("PAUSE");
	m_titleTxt->SetColor(1.0f, 0.0f, 1.0f);
	m_titleTxt->ChangeFontSize(48);


	//パネル操作説明テキスト
	m_descTxt = new Text(
		"Press any Key to Back to the Game..."
	);
	m_descTxt->SetColor(0.2f, 0.2f, 0.2f);
	m_descTxt->ChangeFontSize(24);


	//パネルボタン押下時SE読み込み
	m_decisionSE = new Audio("assets/aud/se/decision3.mp3");
	m_decisionSE->volume = 1.0f;


	//シーンフェード用オブジェクト作成
	m_fadeOuter = new SceneFadeOuter();


	//パネルボタンサイズ
	int btnw = 200;
	int btnh = 50;

	//タイトルへ、パネルボタン設定
	Text* toTitleTxt = new Text("タイトルへ");
	toTitleTxt->ChangeFontSize(24);
	toTitleTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button0 = new Button(new Image(""), toTitleTxt,
		25, (int)scrh - btnh - 100,
		btnw, btnh);

	//ボタンクリック時、
	m_button0->SetOnClick([=]() {
		//シーンフェードアウト時SE再生
		m_decisionSE->Play();
		//タイトルシーンへ遷移
		//m_fadeOuter->SetTrigger("TitleScene");
		//SceneManager::LoadScene("TitleScene");
		});


	//ゲームへ戻る、パネルボタン設定
	Text* toGameTxt = new Text("ゲームへ戻る");
	toGameTxt->ChangeFontSize(24);
	toGameTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button1 = new Button(new Image(""), toGameTxt,
		(int)scrw / 2 - btnw / 2, (int)scrh - btnh - 100,
		btnw, btnh);
	m_button1->SetOnClick([=]() {
		isActive = !isActive;
		});


	//初めから、パネルボタン設定
	Text* reTxt = new Text("初めから");
	reTxt->ChangeFontSize(24);
	reTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_button2 = new Button(new Image(""), reTxt,
		(int)scrw - btnw - 25, (int)scrh - btnh - 100,
		btnw, btnh);
	m_button2->SetOnClick([=]() {
		//シーンフェードアウト時SE再生
		m_decisionSE->Play();
		//メインシーンへ遷移
		//m_fadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
		});
}

Panel::~Panel()
{
	//メモリ解放
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
	//パネルアクティブ時、
	if (isActive) {
		//ボタン更新処理
		m_button0->Update();
		m_button1->Update();
		m_button2->Update();
	}
}

void Panel::Render()
{
	//アクティブ時のみ、描画
	if (!isActive) return;

	//描画領域幅高さ
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//パネル画像描画
	m_img->Render(0, 0, scrw, scrh);

	//パネル見出し文字描画
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 100);

	//パネル説明テキスト描画
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(100, 300);

	//ボタン描画
	m_button0->Render();
	m_button1->Render();
	m_button2->Render();
}

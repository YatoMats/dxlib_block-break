#include "ResultScene.h"
#include "DataManager.h"
#include "SceneFader.h"

#ifndef Release
#define	Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

void ResultScene::Start()
{
	//シーンフェード用オブジェクト作成
	m_sceneFadeInner = new SceneFadeInner();
	m_sceneFadeOuter = new SceneFadeOuter();

	m_sceneFadeSE = new Audio("assets/aud/se/decision3.mp3");
	m_sceneFadeSE->volume = 1.0f;


	//標準フォントサイズ設定
	Text::SetDefaultFontSize(28);


	//背景画像読み込み
	m_bgImg = new Image("assets/img/cosmos.png");
	m_bgImg->alpha = 0.7f;


	//タイトルテキスト作成
	m_titleTxt = new Text("GAME CLEAR!");
	m_titleTxt->SetColor(1, 1, 0);
	m_titleTxt->ChangeFontSize(44);

	//説明文テキスト作成
	m_descTxt = new Text("Press any Button to ReStart..");
	m_descTxt->SetColor(0, 1, 0);


	//リザルトデータの受け取り
	ResultData dat = DataManager::GetResultData();

	//ゲーム失敗なら、
	if (!dat.isSuccess)
	{
		//タイトルテキストを失敗時テキストに書き換え
		m_titleTxt->SetText("GAME OVER...");
		m_titleTxt->SetColor(1, 0, 1);
		//失敗時BGM読み込み
		m_bgm = new Audio("assets/aud/bgm/sad_bgm.mp3");
		m_bgm->volume = 0.3f;
		m_bgm->Play();

		return;
	}
	else {
		//成功時BGM読み込み
		m_bgm = new Audio("assets/aud/bgm/rpg_victory.mp3");
		m_bgm->volume = 0.3f;
	}

	//リザルトデータを説明テキストに追加書き込み
	std::string descStr = "";
	descStr += "SCORE:" + std::to_string(dat.score) + " \n";
	descStr += "HP:" + std::to_string(dat.hp) + " \n";

	//分秒変換
	int sec = dat.time % 60;
	int min = dat.time / 60 % 60;
	//文字列変換
	std::string minStr = std::to_string(min);
	std::string secStr = std::to_string(sec);
	//ゼロ埋め
	if (sec < 10) secStr = "0" + secStr;
	if (min < 10) minStr = "0" + minStr;
	//時間表示用テキストに設定
	std::string timeStr = "ClearTime " + minStr + ":" + secStr;
	descStr += timeStr;

	//説明テキストに上記文字列を追加.
	m_descTxt->SetText(m_descTxt->GetText() + " \n\n" + descStr);

	//BGM再生
	m_bgm->isLooping = true;
	m_bgm->volume = 0.3f;
	m_bgm->Play();
}

ResultScene::~ResultScene()
{
	//メモリ解放
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

	//上記以外の、いずれかのキーが押されたら、
	else if (InputManager::GetAnyKeyEnter()) 
	{
		//SE再生
		m_sceneFadeSE->Play();

		//メインシーンへ戻る
		m_sceneFadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
	}

	//シーンフェード更新処理
	m_sceneFadeInner->Update();
	m_sceneFadeOuter->Update();
}

void ResultScene::Render()
{
	//スクリーン幅高さ
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//背景画像描画
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//タイトルテキスト描画
	int tw = m_titleTxt->GetStringWidth();
	m_titleTxt->Render(scrw / 2 - tw / 2, 150);

	//説明文テキスト描画
	int dw = m_descTxt->GetStringWidth();
	m_descTxt->Render(scrw / 2 - dw / 2, scrh / 2);

	//シーンフェード用パネル描画
	m_sceneFadeInner->Render();
	m_sceneFadeOuter->Render();
}

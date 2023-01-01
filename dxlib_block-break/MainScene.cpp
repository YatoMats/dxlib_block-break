#include "MainScene.h"
#include <windows.h>
#include "Actor.h"
#include "Command.h"
#include "Collision.h"
#include "SoundEffectCommand.h"
#include "Button.h"
#include "SceneFader.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

//TODO:パドルを円形に。衝突後、ボールの押し出し処理を
// 
//TODO: 時間経過でボール速度アップ
//TODO:ウィンドウサイズに応じて、ブロック生成数などを変える

//TODO:ポーズパネルクラス
//TODO:HPUIクラス
//TODO:TimerUIクラス

//TODO:UI Slider
//TODO:UI InputField
//TODO:Config 

void MainScene::Start()
{
	//乱数シード値設定
	srand((unsigned int)time(NULL));

	//標準のフォントサイズを設定
	Text::SetDefaultFontSize(33);

	//スクリーン幅高さ
	float scrw = (float)App::GetResolutionWidth();
	float scrh = (float)App::GetResolutionHeight();


	//BGM
	m_bgm = new Audio("assets/aud/bgm/newworld.mp3");
	m_bgm->isLooping = true;
	m_bgm->volume = 0.33f;
	m_bgm->Play();

	//背景画像
	m_bgImg = new Image("assets/img/cosmos.png");


	//フェード用オブジェクト作成
	m_fadeOuter = new SceneFadeOuter();
	m_fadeInner = new SceneFadeInner();

	//シーンフェードアウト時SE
	m_faderSE = new Audio("assets/aud/se/decision3.mp3");
	m_faderSE->volume = 1.0f;


	//HP表示用テキスト初期設定
	m_hpText = new Text("HP:");// +std::to_string(m_hp));
	m_hpText->SetColor(0, 0.8f, 0);

	//HP表示用ハートUI画像読み込み
	for (int i = 0; i < m_hp; i++) {
		Image* h = new Image("assets/img/heart.png");
		m_heartImgs.push_back(h);
	}


	//時間表示用テキスト
	m_timeText = new Text("TIME 00:00");
	m_timeText->SetColor(0, 0.8f, 0);


	//パネル設定
	m_panelImg = new Image("");
	m_panelImg->alpha = 0.93f;
	m_panelImg->SetColor(0.8f, 0.8f, 0.8f);

	//パネルタイトルテキスト
	m_panelTitle = new Text("PAUSE");
	m_panelTitle->SetColor(1.0f, 0.0f, 1.0f);
	m_panelTitle->ChangeFontSize(44);

	//パネル操作説明テキスト
	m_panelDesc = new Text(
		"Press any Key to Back to the Game..."
	);
	m_panelDesc->SetColor(0.2f, 0.2f, 0.2f);


	//パネルボタンサイズ
	int btnw = 200;
	int btnh = 50;

	//タイトルへ、パネルボタン設定
	Text* toTitleTxt = new Text("タイトルへ");
	toTitleTxt->ChangeFontSize(24);
	toTitleTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnTitle = new Button(new Image(""), toTitleTxt ,
		25, (int)scrh - btnh - 100,
		btnw, btnh);
	//ボタンクリック時、
	m_pnlBtnTitle->SetOnClick([=]() {
		//シーンフェードアウト時SE再生
		m_faderSE->Play();
		//タイトルシーンへ遷移
		m_fadeOuter->SetTrigger("TitleScene");
		//SceneManager::LoadScene("TitleScene");
		});

	//ゲームへ戻る、パネルボタン設定
	Text* toGameTxt = new Text("ゲームへ戻る");
	toGameTxt->ChangeFontSize(24);
	toGameTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnGame = new Button(new Image(""), toGameTxt,
		(int)scrw / 2 - btnw / 2, (int)scrh - btnh - 100,
		btnw, btnh);
	m_pnlBtnGame->SetOnClick([=]() {
		m_isPaused = !m_isPaused;
		});

	//初めから、パネルボタン設定
	Text* reTxt = new Text("初めから");
	reTxt->ChangeFontSize(24);
	reTxt->SetColor(0.1f, 0.1f, 0.1f);

	m_pnlBtnRe = new Button(new Image(""), reTxt,
		(int)scrw - btnw - 25, (int)scrh - btnh - 100,
		btnw, btnh);
	m_pnlBtnRe->SetOnClick([=]() {
		//シーンフェードアウト時SE再生
		m_faderSE->Play();
		//メインシーンへ遷移
		m_fadeOuter->SetTrigger("MainScene");
		//SceneManager::LoadScene("MainScene");
		});

	//パネル生成時SE
	m_pnlPopSE = new Audio("assets/aud/se/decision2.mp3");
	m_pnlPopSE->volume = 0.8f;
	//パネル消失時SE
	m_pnlDeSE = new Audio("assets/aud/se/cancel2.mp3");
	m_pnlDeSE->volume = 1.0f;


	//プレイヤーパドル作成、設定
	Image* pdlImg = new Image("");
	pdlImg->shape = Shape::Circle;
	m_paddle = new Actor(
		pdlImg,				//画像情報
		scrw / 2, scrh - 50,	//位置
		80, 80					//サイズ
	);
	//アクターリストに追加
	m_actors.push_back(m_paddle);


	//ボール画像設定
	Image* ballImg = new Image("");
	ballImg->shape = Shape::Circle;
	//ボール半径
	float br = 38;
	//ボール生成位置x座標をランダムに
	float bx = (float)Math::RandRange((int)br, (int)(scrw - br));
	//ボールアクター
	m_ball = new Actor(
		ballImg,
		bx, m_paddle->pos.y - 75,	//位置
		br, br						//サイズ
	);
	m_actors.push_back(m_ball);


	//ブロック行列の左上位置
	float ox = 120;
	float oy = 120;
	//ブロック間のスペース
	float sx = 10;
	float sy = 10;
	//ブロック幅高さ
	float w = 60;
	float h = 60;
	//ブロック行列を作成
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 8; x++) {
			//ブロック画像
			Image* blockImg = new Image("");
			blockImg->shape = Shape::Circle;
			//ブロックアクター設定
			Actor* block = new Actor(
				blockImg,
				ox + x * (w + sx), oy + y * (h + sy),	//位置
				w, h									//サイズ
			);
			//アクターリストに追加
			m_actors.push_back(block);

			//ブロック数データを加算
			m_blockCounts++;
		}
	}

	//パドルへの衝突時SE
	m_paddleSE = new Audio("assets/aud/se/decision.mp3");
	m_paddleSE->volume = 1.0f;
	//ボール落下時SE
	m_fallSE = new Audio("assets/aud/se/bomb.mp3");
	m_fallSE->volume = 1.0f;
	//ブロックとの衝突時SE
	m_blockSE = new Audio("assets/aud/se/cancel.mp3");
	m_blockSE->volume = 1.0f;

	//マウスカーソル位置取得
	m_preMousePos = InputManager::GetMousePos();
}

MainScene::~MainScene()
{
	//メモリ解放処理
	Release(m_bgm);
	Release(m_bgImg);

	Release(m_hpText);
	Release(m_timeText);

	Release(m_paddleSE);
	Release(m_fallSE);
	Release(m_blockSE);

	Release(m_panelImg);
	Release(m_panelTitle);
	Release(m_panelDesc);
	
	Release(m_pnlBtnTitle);
	Release(m_pnlBtnGame);
	Release(m_pnlBtnRe);

	Release(m_pnlPopSE);
	Release(m_pnlDeSE);

	Release(m_fadeInner);
	Release(m_fadeOuter);
	Release(m_faderSE);

	for (Image* h : m_heartImgs) {
		delete h;
	}

	//全アクターの終了処理
	for (Actor* a : m_actors) {
		delete a;
	}
	//残っているコマンドの終了処理
	for (Command* c : m_cmds) {
		delete c;
	}
}

void MainScene::Update()
{
	//シーンフェード更新処理
	m_fadeInner->Update();
	m_fadeOuter->Update();

	//ゲーム終了判定時、
	if (m_isGameOver || m_isGameClear)
	{
		//ゲーム終了時処理
		OnGameEnds();
		return;
	}

	//ゲーム中なら、
	if(!m_isPaused)
	{
		if (InputManager::GetKeyEnter(KEY_ID::ESC) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE) ||
			InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT))
		{
		}
		//ゲーム中に、上記以外のいずれかのキーが押されたら、
		else if (InputManager::GetAnyKeyEnter())
		{
			//パネル生成時SE再生
			m_pnlPopSE->Play();
			//ポーズ中フラグ切り替え
			m_isPaused = !m_isPaused;
		}
	}
	//ポーズ中なら、
	else 
	{
		//ポーズ中処理
		OnGamePause();
		//アクター更新等の処理を飛ばす
		return;
	}

	//ボール落下状態なら、
	if (m_isBallFallen) 
	{
		//ボール落下中の処理
		OnBallFall();
		//アクター更新等の処理を飛ばす
		return;
	}

	//コマンドリストを回す
	/*for (int i = (int)m_cmds.size() - 1; i >= 0; i--) {
		Command* c = m_cmds[i];
		//コマンド更新処理
		c->Execute();
		//コマンド終了なら、コマンドリストから除く
		if (c->isDone) {
			delete c;
			m_cmds.erase(m_cmds.begin() + i);
		}
	}
	//コマンド実行中なら、ゲームを一時停止
	if (m_cmds.size() != 0) return;*/


	//スクリーン幅高さ
	float scrw = (float)App::GetResolutionWidth();
	float scrh = (float)App::GetResolutionHeight();

	//マウスカーソル位置
	Vec2 mp = InputManager::GetMousePos();

	//プレイヤーパドル位置
	Vec2 p = m_paddle->pos;
	//プレイヤーパドルサイズ
	float pw = m_paddle->size.x;
	float ph = m_paddle->size.y;

	//ボール速度
	Vec2 bv = m_ballVeloc;
	//ボール位置
	Vec2 b = m_ball->pos;
	//ボールサイズ
	float br = m_ball->size.x / 2;


	//マウス移動量に応じて、プレイヤー位置を変更
	p.x = mp.x;
	//p.y = mp.y;
	//プレイヤー位置を、範囲内へ押し戻し
	if (p.x - pw / 2 < 0) p.x = pw / 2;
	else if (scrw < p.x + pw / 2) p.x = scrw - pw / 2;


	//ボール速度ベクトルが水平に近いなら、軌道を少し曲げる

	//ボール軌道が水平に近く、
	if (Math::Abs(bv.y) < 0.03f) {
		//右向き
		if (0 < bv.x) {
			//下向きなら、時計回りに回転
			if (0 < bv.y) bv.Rotate(3);
			//上向きなら、反時計回りに回転
			else bv.Rotate(-3);
		}
		//左向き
		else {
			//下向きなら、反時計回りに回転
			if (0 < bv.y) bv.Rotate(-3);
			//上向きなら、時計回りに回転
			else bv.Rotate(3);
		}
	}
	//ボール軌道が垂直に近く、
	/*else if (Math::Abs(bv.x) < 0.03f) {
		//下向き
		if (0 < bv.y) {
			//右向きなら、時計回りに回転
			if (0 < bv.x) bv.Rotate(3);
			//左向きなら、反時計回りに回転
			else bv.Rotate(-3);
		}
		//上向き
		else {
			//右向きなら、時計回りに回転
			if (0 < bv.x) bv.Rotate(3);
			//左向きなら、反時計回りに回転
			else bv.Rotate(-3);
		}
	}*/


	//速度(pix/s)に応じて、ボール移動
	b += bv * 1.0f / (float)App::GetFrameRate();

	//ボールがステージ端に到達したら、跳ね返し
	//ステージ右端衝突時、
	if (b.x - br < 0) {
		b.x = br;
		bv.x *= -1.0f;
	}
	//左端
	else if (scrw < b.x + br) {
		b.x = scrw - br;
		bv.x *= -1.0f;
	}
	//上端
	if (b.y - br < 0) {
		b.y = br;
		bv.y *= -1.0f;
	}
	//ボールがステージ底に落ちたら、
	else if (scrh < b.y - br)
	{
		//ボール位置を戻す
		//ボール生成位置x座標をランダムに
		b.x = (float)Math::RandRange((int)br, (int)(scrw - br));
		b.y = p.y - 100;
		//ボール速度を初期値に
		bv = m_ballStartVeloc;

		//ボールが落下した瞬間の処理
		OnBallFallEnter();
	}


	//ボールとブロックとの距離の2乗を計算
	float dpow = b.DistancePow(p);
	float pr = pw / 2;
	//ボールとブロックが当たっていたら、
	if (dpow < Math::Pow2(br + pr))
	{
		//ボール速度ベクトルを反射
		bv.Reflect(p.DirectionTo(b));

		//SE再生
		m_paddleSE->Play();
	}
	//ボールがパドルに当たったら、
	//if (HitCheck::CircleToBox(b, br, p, pw, ph))
	/*if (HitCheck::CircleToCircle(b, br, p, pw))
	{						
		//ボール速度ベクトルを反射
		bv.Reflect(p.DirectionTo(b));

		//矩形左上
		/*Vec2 min = Vec2(p.x - pw / 2, p.y - ph / 2);
		//矩形右下
		Vec2 max = Vec2(p.x + pw / 2, p.y + ph / 2);

		//角に当たった場合の反射計算
		//矩形4頂点と円との当たり判定
		if (b.DistancePow(min) < Math::Pow2(br)) {
			//ボールがパドル左上頂点より左上側なら、
			if ((b.x < min.x) && (b.y < min.y)) {
				//押し戻し処理
				//ボール位置をパドルの上に
				//b.y = p.y - ph / 2 - br;
				//反射ベクトル計算
				bv.Reflect(min.DirectionTo(b));
			}
		}
		else if (b.DistancePow(Vec2(max.x, min.y)) < Math::Pow2(br)) {
			//ボールがパドル右上頂点より右上側なら、
			if ((max.x < b.x) && (b.y < min.y)) {
				//反射ベクトル計算
				bv.Reflect(Vec2(max.x, min.y).DirectionTo(b));
			}
		}
		/*else if (b.DistancePow(Vec2(min.x, max.y)) < Math::Pow2(br)) {
			//反射ベクトル計算
			bv.Reflect(Vec2(min.x, max.y).DirectionTo(b));
		}
		else if (b.DistancePow(max) < Math::Pow2(br)) {
			//反射ベクトル計算
			bv.Reflect(max.DirectionTo(b));
		}*//*
		//角以外の反射計算
		else
		{
			//ボール位置をパドルの上に
			b.y = p.y - ph / 2 - br;
			//ボール速度ベクトルを反射
			bv.y *= -1.0f;
		}
		//SE再生
		m_paddleSE->Play();
	}*/

	//ボールとブロックとの当たり判定
	for (int i = (int)m_actors.size() - 1; i >= 2; i--) {
		Actor* a = m_actors[i];

		//ボール半径
		float r = m_ball->size.x / 2;
		//ブロック半径
		float r2 = a->size.x / 2;
		//ブロック位置
		Vec2 ap = a->pos;

		//ボールとブロックとの距離の2乗を計算
		float dpow = b.DistancePow(ap);

		//ボールとブロックが当たっていたら、
		if (dpow < Math::Pow(r + r2, 2.0f))
		{
			//ボール速度ベクトルを反射
			bv.Reflect(ap.DirectionTo(b));

			//ブロックを破壊
			delete a;
			//リストから破棄
			m_actors.erase(m_actors.begin() + i);
			//ブロック数が0以下になったら、ゲームクリア判定に
			if (--m_blockCounts <= 0) m_isGameClear = true;

			//SE再生
			m_blockSE->Play();
		}
	}

	//パドルの位置変異確定
	m_paddle->pos = p;
	//ボールの位置、速度変異確定
	m_ball->pos = b;
	m_ballVeloc = bv;
	//マウス位置を保存
	m_preMousePos = mp;


	//経過時間計算
	m_time += 1.0f / (float)App::GetFrameRate();
	//分秒変換
	int sec = (int)m_time % 60;
	int min = (int)m_time / 60 % 60;
	//文字列変換
	std::string minStr = std::to_string(min);
	std::string secStr = std::to_string(sec);
	//ゼロ埋め
	if (sec < 10) secStr = "0" + secStr;
	if (min < 10) minStr = "0" + minStr;
	//時間表示用テキストに設定
	m_timeText->SetText("TIME " + minStr + ":" + secStr);
}

void MainScene::Render()
{
	//スクリーン幅高さ
	int scrw = App::GetResolutionWidth();
	int scrh = App::GetResolutionHeight();

	//背景画像の描画
	m_bgImg->Render(-1, -1, scrw + 1, scrh + 1);

	//全アクターの描画
	for (Actor* a : m_actors) {
		a->Render();
	}

	//UI描画
	//HP用ハート画像描画
	for (int i = 0; i < m_heartImgs.size(); i++) {
		m_heartImgs[i]->Render(i * 50 + scrw / 2/*+300*/, 10, 50, 50);
	}
	//プレイヤーHPテキスト描画
	m_hpText->Render(scrw / 2 - 50, 15);

	//時間表示用テキスト描画
	m_timeText->Render(50, 10);

	//ポーズ時のパネルを描画
	if (m_isPaused) 
	{
		m_panelImg->Render(0, 0, scrw, scrh);

		int tw = m_panelTitle->GetStringWidth();
		m_panelTitle->Render(scrw / 2 - tw / 2, 100);

		int dw = m_panelDesc->GetStringWidth();
		m_panelDesc->Render(/*100*/scrw / 2 - dw / 2, 300);

		m_pnlBtnTitle->Render();
		m_pnlBtnGame->Render();
		m_pnlBtnRe->Render();
	}

	//フェード用パネル描画
	m_fadeInner->Render();
	m_fadeOuter->Render();
}

void MainScene::OnBallFallEnter()
{
	//ボール落下状態に
	//m_isBallFallen = true;

	//SE再生
	m_fallSE->Play();
	
	//HPを減らす
	if (--m_hp <= 0) {
		//HPが０以下になったら、
		//ゲーム終了フラグを立てる
		m_isGameOver = true;
	}
	//HPが1以下になったら、赤文字に
	else if (m_hp <= 1) {
		m_hpText->SetColor(1.0f, 0, 0);
	}
	//HPが2以下になったら、黄文字に
	else if (m_hp <= 2) {
		m_hpText->SetColor(1.0f, 1.0f, 0);
	}

	//HP表示更新
	//m_hpText->SetText("HP:" + std::to_string(m_hp));

	//HP表示用ハート画像を減らす
	if (m_hp >= 0)
	{
		Release(m_heartImgs[m_hp]);
		m_heartImgs.erase(m_heartImgs.begin() + m_hp);
	}
}

void MainScene::OnBallFall()
{
	//少し待ってから、位置と速度を戻す処理を
	/*m_ballFallTimer += 1.0f / (float)App::fps;
	if (m_ballFallTimer > m_ballFallSpan)
	{
		m_ballFallTimer = 0.0f;

		m_ball->pos = Vec2(0, 0);
		m_ballVeloc = m_ballStartVeloc;

		m_isBallFall = false;
	}*/
}

void MainScene::OnGamePause()
{
	//デバッグ用操作
	/*if (InputManager::GetKeyEnter(KEY_ID::R)) {
		//ゲーム終了時パラメータ情報を一時保存
		ResultData result;
		result.isSuccess = true;//m_isGameClear;
		result.hp = m_hp;
		result.time = (int)m_time;

		//スコア計算
		int hpPt = m_hp * m_hp * 100;
		int t = 1;
		//if (m_time > 0)
		t = (int)m_time;
		int timePt = 10000 - t * 50;
		if (timePt < 0) timePt = 1000;
		result.score = hpPt + timePt;

		DataManager::SetResultData(result);

		m_fadeOuter->SetTrigger("ResultScene");
	}

	else*/
	if (InputManager::GetKeyEnter(KEY_ID::ESC)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_LEFT)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_MIDDLE)||
		InputManager::GetKeyEnter(KEY_ID::MOUSE_RIGHT)
		)
	{
	}
	//ポーズ中に、上記以外のいずれかのキーが押されたら、
	else if (InputManager::GetAnyKeyEnter())
	{
		//パネル消失時SE再生
		m_pnlDeSE->Play();

		//ポーズ中フラグ切り替え
		m_isPaused = !m_isPaused;
	}

	//パネルボタン更新処理
	m_pnlBtnGame->Update();
	m_pnlBtnRe->Update();
	m_pnlBtnTitle->Update();
}

void MainScene::OnGameEnds()
{
	//ゲーム終了時パラメータ情報を一時保存
	ResultData result;
	result.isSuccess = m_isGameClear;
	result.hp = m_hp;
	result.time = (int)m_time;

	//スコア計算
	int hpPt = m_hp * m_hp * 100;
	int t = 1;
	//if (m_time > 0)
		t = (int)m_time;
	int timePt = 10000 - t * 50;
	if (timePt < 0) timePt = 1000;
	result.score = hpPt + timePt;

	DataManager::SetResultData(result);

	//結果シーンに遷移
	m_fadeOuter->SetTrigger("ResultScene");
	//SceneManager::LoadScene("ResultScene");
}

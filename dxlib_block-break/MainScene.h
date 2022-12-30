#pragma once
#include "Scene.h"
#include "Vec2.h"
#include <vector>
#include "DataManager.h"

class Actor;
class Command;
class Button;
class SceneFadeOuter;
class SceneFadeInner;

class MainScene : public Scene 
{
	//全アクターの配列
	std::vector<Actor*> m_actors;

	//コマンドリスト
	std::vector<Command*> m_cmds;

	//プレイヤーパドル
	Actor* m_paddle;
	//ボール
	Actor* m_ball;

	//SE
	Audio* m_paddleSE;
	Audio* m_blockSE;
	Audio* m_fallSE;

	//BGM
	Audio* m_bgm;
	//背景画像
	Image* m_bgImg;

	//時間表示用テキスト
	Text* m_timeText;
	//HP表示用テキスト
	Text* m_hpText;

	//HP表示用ハート画像
	std::vector<Image*> m_heartImgs;

	//ボール初速
	const Vec2 m_ballStartVeloc = Vec2(300, -300);
	//ボール速度
	Vec2 m_ballVeloc = m_ballStartVeloc;

	//前フレームでのマウス位置
	Vec2 m_preMousePos;

	//プレイヤーHP
	int m_hp = 3;
	//ゲーム中の経過時間
	float m_time = 0;

	//ゲーム上の総ブロック数
	int m_blockCounts = 0;

	//ゲーム失敗フラグ
	bool m_isGameOver = false;
	//ゲーム成功フラグ
	bool m_isGameClear = false;

	//ボール落下後時処理
	bool m_isBallFallen = false;

	//ゲームポーズ中フラグ
	bool m_isPaused = false;
	
	//ポーズ中などでの表示用パネル
	Image* m_panelImg;
	//パネル上のタイトルテキスト
	Text* m_panelTitle;
	//パネル上の操作説明等のテキスト
	Text* m_panelDesc;
	//パネル上のボタン
	Button* m_pnlBtnTitle;
	Button* m_pnlBtnRe;
	Button* m_pnlBtnGame;

	//ポーズパネル生成時SE
	Audio* m_pnlPopSE;
	//ポーズパネル破棄時SE
	Audio* m_pnlDeSE;

	//リザルトシーンへ渡す、ゲームの結果情報
	ResultData m_resultData;

	//シーンフェード用
	SceneFadeInner* m_fadeInner;
	SceneFadeOuter* m_fadeOuter;

	//シーンフェードアウト時SE
	Audio* m_faderSE;

public:
	//ブロック崩しゲーム終了処理
	~MainScene();
	//ブロック崩しゲーム開始処理
	void Start()override;
	//ブロック崩しゲーム更新処理
	void Update()override;
	//ブロック崩しゲーム描画処理
	void Render()override;

	//ボール落下した瞬間の処理
	void OnBallFallEnter();
	//ボール落下後状態時処理
	void OnBallFall();

	//ゲームポーズ時処理
	void OnGamePause();

	//ゲーム終了時処理
	void OnGameEnds();
};
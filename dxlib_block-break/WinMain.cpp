#include "DxLib.h"
#include <Windows.h>
#include <time.h>
#include "App.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "MainScene.h"
#include "TitleScene.h"
#include "ResultScene.h"

#pragma comment(lib,"winmm.lib")

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

int WINAPI WinMain
(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//乱数シード値設定
	srand((unsigned int)time(NULL));

	//スクリーンサイズの取得
	int dispx = GetSystemMetrics(SM_CXSCREEN);
	int dispy = GetSystemMetrics(SM_CYSCREEN);
	
	//ウィンドウ解像度設定
	App::SetResolution(dispy - 95, dispy - 95);

	//ウィンドウモード変更
	ChangeWindowMode(true);
	//ウィンドウ破棄をアプリ側で操作できるように
	SetWindowUserCloseEnableFlag(false);
	// 画面サイズ設定
	SetGraphMode(App::GetResolutionWidth(), App::GetResolutionHeight(), 32);
	//背景色設定
	SetBackgroundColor(123, 123, 123);
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	//マウスカーソル表示設定
	//SetMouseDispFlag(FALSE);
	

	//入力情報初期化
	InputManager::Init();


	//ゲーム初期化

	//シーンのビルド設定
	SceneManager::RegisterSceneBuild("TitleScene", []() {return new TitleScene(); });
	SceneManager::RegisterSceneBuild("MainScene", []() {return new MainScene(); });
	SceneManager::RegisterSceneBuild("ResultScene", []() {return new ResultScene(); });

	//最初のシーン(TitleScene)の読み込み
	if (!SceneManager::LoadScene(0)) return 0;


	//フレームレート設定
	//分解能を最高値に
	timeBeginPeriod(1);
	//計測開始時刻
	unsigned int startTime = timeGetTime();
	//1フレーム当たりのミリ秒時間
	unsigned int mspf = 1000 / App::GetFrameRate();

	// メインループ
	while (ProcessMessage() == 0 && App::IsPlaying())
	{
		//フレームレート合わせ処理
		unsigned int elapsedTime = timeGetTime() - startTime;
		if (elapsedTime > mspf)
		{
			startTime = timeGetTime();

			//ウィンドウ×ボタンクリック時など、ウィンドウ閉じ操作時、または、ESCキー押下時、
			if (GetWindowUserCloseFlag(TRUE) || InputManager::GetKeyEnter(KEY_ID::ESC) //|| GetKeyState(VK_ESCAPE) < 0
				) 
			{
				//アプリケーション終了確認ウィンドウ表示
				App::PopUpQuitQuestion();
			}

			//入力情報更新
			InputManager::Update();

			//ゲームシーンの更新
			SceneManager::Update();

			// 画面を初期化する
			ClearDrawScreen();

			//ゲームシーンの描画
			SceneManager::Render();

			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
		}
	}

	//ゲーム終了処理
	SceneManager::Fin();

	DxLib::DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}
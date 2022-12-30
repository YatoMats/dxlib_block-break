#pragma once

class App
{
	static bool s_isPlaying;

	static int resolutionWidth;
	static int resolutionHeight;
	static const int fps;
public:
	//解像度を設定
	static void SetResolution(int x, int y) { resolutionWidth = x; resolutionHeight = y; }

	//ウィンドウ横解像度を取得
	static int GetResolutionWidth() { return resolutionWidth; }
	//ウィンドウ縦解像度を取得
	static int GetResolutionHeight() { return resolutionHeight; }

	//1秒当たりに処理するフレーム数を取得
	static int GetFrameRate() { return fps; }


	//アプリケーションが稼働中か
	static bool IsPlaying() { return s_isPlaying; }
	//アプリケーションを終了する
	static void Quit() { s_isPlaying = false; }

	//本当に終了するか質問するポップアップウィンドウを出す
	static void PopUpQuitQuestion();
};
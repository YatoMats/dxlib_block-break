#include "App.h"
#include <Windows.h>

bool App::s_isPlaying = true;

int App::resolutionWidth = 720;
int App::resolutionHeight = 720;

const int App::fps = 60;

void App::PopUpQuitQuestion()
{
	//マウスカーソル表示設定
	//SetMouseDispFlag(TRUE);
	
	//終了確認ウィンドウ表示
	if (IDYES == MessageBox(nullptr, TEXT("アプリケーションを終了しますか？"), TEXT("確認"), MB_YESNO)) {
		//YESが選択されたら、アプリケーション稼働中フラグを折る
		s_isPlaying = false;
	}
	
	//マウスカーソル表示設定
	//SetMouseDispFlag(FALSE);
}

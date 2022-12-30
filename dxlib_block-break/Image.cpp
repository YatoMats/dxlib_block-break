#include "Image.h"
#include "DxLib.h"

Image::Image(const char* path):
	m_graphHandle(-1)
{
	if (path == "") {
		return;
	}

	//ファイルパスから画像データ読み込み
	m_graphHandle = LoadGraph(path);
	if (m_graphHandle == -1) {
		MessageBox(nullptr, "画像ファイルの読み込みに失敗しました。", "ERROR", MB_OK);
	}
}

Image::~Image()
{
	DeleteGraph(m_graphHandle);
}

void Image::Render(int x, int y, int w, int h)
{
	int color = GetColor(
		(int)(m_color[0] * 255.0f), (int)(m_color[1] * 255.0f), (int)(m_color[2] * 255.0f)
	);

	//アルファブレンドモード設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255.0f));

	//画像データが読み込まれていないなら、図形を描画
	if (m_graphHandle == -1) {
		switch (shape)
		{
		case Shape::Circle:
			DrawCircle(x + w / 2, y + h / 2, w / 2, color);
			break;
		case Shape::Box:
			DrawBox(x, y, x + w, y + h, color, TRUE);
			break;
		default:
			break;
		}
		return;
	}
	//画像描画
	DrawExtendGraph(x, y, x + w, y + h, m_graphHandle, TRUE);

	//ブレンドモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

#pragma once
#include <functional>
#include <Windows.h>

class Image;
class Text;

class Button {
	//ボタン画像
	Image* m_img;
	//ボタンテキスト
	Text* m_txt;

	//ボタンが押されたかどうか
	bool m_isPushed = false;
	//マウスカーソルがボタンの上にホバー中かどうか
	bool m_isHovered = false;

	//通常時の画像色
	float m_imageColor[3] = { 1.0f,1.0f,1.0f };
	//マウスホバー時の画像の色
	float m_hoverColor[3] = { 0.7f,0.7f,0.7f };

	//ボタン押下時イベント
	std::function<void()> m_onClick = []() {};

public:
	//ボタン左上x位置座標
	int x;
	//ボタン左上y位置座標
	int y;
	//ボタン幅
	int width;
	//ボタン高さ
	int height;

public:
	/// <summary>
	/// ボタン作成
	/// </summary>
	/// <param name="img">ボタン画像情報</param>
	/// <param name="txt">ボタンテキスト情報</param>
	/// <param name="_x">ボタン左上位置x座標</param>
	/// <param name="_y">ボタン左上位置y座標</param>
	/// <param name="w">ボタン横幅</param>
	/// <param name="h">ボタン高さ</param>
	Button(Image* img, Text* txt, int _x = 50, int _y = 50, int w = 150, int h = 50)
		:m_img(img), m_txt(txt), x(_x), y(_y), width(w), height(h)
	{

	}
	~Button();

	//押下などの確認
	void Update();
	//ボタン描画
	void Render();

	//ボタン押下時の処理を設定
	void SetOnClick(std::function<void()> func) { m_onClick = func; }

	//ボタンが押されたかどうか
	bool IsPushed(){
		return m_isPushed;
	}
	//マウスカーソルがボタンの上でホバー中かどうか
	bool IsHovered() {
		return m_isHovered;
	}

	void SetText(Text* txt);

	void SetImageColor(float r, float g, float b) {
		m_imageColor[0] = r; m_imageColor[1] = g; m_imageColor[2] = b;
	}
	void SetHoverImageColor(float r, float g, float b) {
		m_hoverColor[0] = r; m_hoverColor[1] = g; m_hoverColor[2] = b; 
	}
};
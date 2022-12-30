#include "Button.h"
#include "InputManager.h"
#include "Image.h"
#include "Text.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

Button::~Button()
{
	Release(m_img);
	Release(m_txt);
}

void Button::Update()
{
	m_isPushed = false;
	m_isHovered = false;

	m_img->SetColor(m_imageColor[0], m_imageColor[1], m_imageColor[2]);

	//マウス位置を取得
	Vec2 m = InputManager::GetMousePos();

	//マウス位置のボタン範囲内判定
	if ((x < m.x && m.x < x + width) &&
		(y < m.y && m.y < y + height))
	{
		//ホバー中フラグを立てる
		m_isHovered = true;
		//ホバー時処理
		m_img->SetColor(m_hoverColor[0], m_hoverColor[1], m_hoverColor[2]);

		//マウスボタンがクリックされていたら、
		if (InputManager::GetKeyExit(KEY_ID::MOUSE_LEFT)) 
		{
			//ボタン押下フラグを立てる
			m_isPushed = true;
			
			//ボタン押下時処理
			m_onClick();
		}
	}
}

void Button::Render()
{
	//ボタン画像を描画
	m_img->Render(x, y, width, height);

	//ボタンテキストを描画
	m_txt->Render(x + 10, y + 10);
}

void Button::SetText(Text* txt)
{
	Release(m_txt);
	m_txt = txt;
}

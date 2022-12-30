#include "Text.h"
#include "DxLib.h"

Text::Text(const std::string& text) 
	: m_text(text)
{
	//getstring
}

Text::~Text()
{
	DeleteFontToHandle(m_fontHandle);
}

void Text::SetDefaultFontSize(int size) 
{
	//デフォルト文字サイズ変更
	SetFontSize(size);
}

void Text::ChangeFontSize(int size, int thick)
{
	//既にフォントハンドルが設定されていたら、先に解放処理を。
	if (m_fontHandle != -1) {
		DeleteFontToHandle(m_fontHandle);
	}

	m_fontHandle = DxLib::CreateFontToHandle(NULL, size, thick);
	if (m_fontHandle == -1) {
		MessageBox(nullptr, "フォントの作成に失敗したため、フォントサイズの変更ができませんでした。", "ERROR", MB_OK);
	}
}

void Text::CreateTextFont(const std::string& fontName, int size, int thick)
{
	//既にフォントハンドルが設定されていたら、先に解放処理を。
	if (m_fontHandle != -1) {
		DeleteFontToHandle(m_fontHandle);
	}

	m_fontHandle = DxLib::CreateFontToHandle(fontName.c_str(), size, thick);
	if (m_fontHandle == -1) {
		MessageBox(nullptr, "フォントの作成に失敗しました。", "ERROR", MB_OK);
	}
}

int Text::GetStringWidth()
{
	int r = -1;
	if (m_fontHandle != -1) {
		r = GetDrawNStringWidthToHandle(m_text.c_str(), strlen(m_text.c_str()), m_fontHandle);
	}
	else {
		r = GetDrawStringWidth(m_text.c_str(), (int)strlen(m_text.c_str()));
	}

	if (r == -1) {
		MessageBox(nullptr, "テキスト文字列の横幅サイズの取得に失敗しました。", "ERROR", MB_OK);
	}
	return r;
}

void Text::SetColor(float r, float g, float b)
{
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
}

void Text::Render(int x, int y)
{
	//文字色
	int color = GetColor((int)(m_color[0] * 255.0f), (int)(m_color[1] * 255.0f), (int)(m_color[2] * 255.0f));

	//フォントハンドルが設定されているなら、
	if (m_fontHandle != -1)
	{
		//フォントハンドルから文字列を描画
		DrawStringToHandle(x, y, m_text.c_str(), color, m_fontHandle);
		return;
	}

	//文字列描画
	DrawString(x, y, m_text.c_str(), color);
}

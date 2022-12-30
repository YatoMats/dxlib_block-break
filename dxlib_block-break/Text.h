#pragma once
#include <string>

class Text {
	//描画する文字列
	std::string m_text = "Text";
	//文字色
	float m_color[3] = { 0.8f,0.8f,0.8f };

	//規定のフォントサイズ
	static int s_defaultFontSize;

	//フォントハンドル
	int m_fontHandle = -1;
public:
	Text(const std::string& str = "");
	~Text();

	//テキストを描画
	void Render(int x, int y);

	//表示用テキストを変更
	void SetText(const std::string& text) { m_text = text; }
	const std::string& GetText() { return m_text; }

	//各成分ごとに 0.0f～1.0f までの範囲で、フォントの色を設定する
	void SetColor(float red, float green, float blue);

	//規定フォントサイズを変更
	static void SetDefaultFontSize(int size);

	//新たにフォントを作成して、フォントサイズを変更
	void ChangeFontSize(int size, int thick = -1);
	
	//フォント作成
	void CreateTextFont(const std::string& fontName, int size, int thick = -1);

	//描画する文字列の幅を取得
	int GetStringWidth();
};
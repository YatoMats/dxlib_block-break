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
	//�f�t�H���g�����T�C�Y�ύX
	SetFontSize(size);
}

void Text::ChangeFontSize(int size, int thick)
{
	//���Ƀt�H���g�n���h�����ݒ肳��Ă�����A��ɉ���������B
	if (m_fontHandle != -1) {
		DeleteFontToHandle(m_fontHandle);
	}

	m_fontHandle = DxLib::CreateFontToHandle(NULL, size, thick);
	if (m_fontHandle == -1) {
		MessageBox(nullptr, "�t�H���g�̍쐬�Ɏ��s�������߁A�t�H���g�T�C�Y�̕ύX���ł��܂���ł����B", "ERROR", MB_OK);
	}
}

void Text::CreateTextFont(const std::string& fontName, int size, int thick)
{
	//���Ƀt�H���g�n���h�����ݒ肳��Ă�����A��ɉ���������B
	if (m_fontHandle != -1) {
		DeleteFontToHandle(m_fontHandle);
	}

	m_fontHandle = DxLib::CreateFontToHandle(fontName.c_str(), size, thick);
	if (m_fontHandle == -1) {
		MessageBox(nullptr, "�t�H���g�̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK);
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
		MessageBox(nullptr, "�e�L�X�g������̉����T�C�Y�̎擾�Ɏ��s���܂����B", "ERROR", MB_OK);
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
	//�����F
	int color = GetColor((int)(m_color[0] * 255.0f), (int)(m_color[1] * 255.0f), (int)(m_color[2] * 255.0f));

	//�t�H���g�n���h�����ݒ肳��Ă���Ȃ�A
	if (m_fontHandle != -1)
	{
		//�t�H���g�n���h�����當�����`��
		DrawStringToHandle(x, y, m_text.c_str(), color, m_fontHandle);
		return;
	}

	//������`��
	DrawString(x, y, m_text.c_str(), color);
}

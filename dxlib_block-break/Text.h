#pragma once
#include <string>

class Text {
	//�`�悷�镶����
	std::string m_text = "Text";
	//�����F
	float m_color[3] = { 0.8f,0.8f,0.8f };

	//�K��̃t�H���g�T�C�Y
	static int s_defaultFontSize;

	//�t�H���g�n���h��
	int m_fontHandle = -1;
public:
	Text(const std::string& str = "");
	~Text();

	//�e�L�X�g��`��
	void Render(int x, int y);

	//�\���p�e�L�X�g��ύX
	void SetText(const std::string& text) { m_text = text; }
	const std::string& GetText() { return m_text; }

	//�e�������Ƃ� 0.0f�`1.0f �܂ł͈̔͂ŁA�t�H���g�̐F��ݒ肷��
	void SetColor(float red, float green, float blue);

	//�K��t�H���g�T�C�Y��ύX
	static void SetDefaultFontSize(int size);

	//�V���Ƀt�H���g���쐬���āA�t�H���g�T�C�Y��ύX
	void ChangeFontSize(int size, int thick = -1);
	
	//�t�H���g�쐬
	void CreateTextFont(const std::string& fontName, int size, int thick = -1);

	//�`�悷�镶����̕����擾
	int GetStringWidth();
};
#pragma once
#include <functional>
#include <Windows.h>

class Image;
class Text;

class Button {
	//�{�^���摜
	Image* m_img;
	//�{�^���e�L�X�g
	Text* m_txt;

	//�{�^���������ꂽ���ǂ���
	bool m_isPushed = false;
	//�}�E�X�J�[�\�����{�^���̏�Ƀz�o�[�����ǂ���
	bool m_isHovered = false;

	//�ʏ펞�̉摜�F
	float m_imageColor[3] = { 1.0f,1.0f,1.0f };
	//�}�E�X�z�o�[���̉摜�̐F
	float m_hoverColor[3] = { 0.7f,0.7f,0.7f };

	//�{�^���������C�x���g
	std::function<void()> m_onClick = []() {};

public:
	//�{�^������x�ʒu���W
	int x;
	//�{�^������y�ʒu���W
	int y;
	//�{�^����
	int width;
	//�{�^������
	int height;

public:
	/// <summary>
	/// �{�^���쐬
	/// </summary>
	/// <param name="img">�{�^���摜���</param>
	/// <param name="txt">�{�^���e�L�X�g���</param>
	/// <param name="_x">�{�^������ʒux���W</param>
	/// <param name="_y">�{�^������ʒuy���W</param>
	/// <param name="w">�{�^������</param>
	/// <param name="h">�{�^������</param>
	Button(Image* img, Text* txt, int _x = 50, int _y = 50, int w = 150, int h = 50)
		:m_img(img), m_txt(txt), x(_x), y(_y), width(w), height(h)
	{

	}
	~Button();

	//�����Ȃǂ̊m�F
	void Update();
	//�{�^���`��
	void Render();

	//�{�^���������̏�����ݒ�
	void SetOnClick(std::function<void()> func) { m_onClick = func; }

	//�{�^���������ꂽ���ǂ���
	bool IsPushed(){
		return m_isPushed;
	}
	//�}�E�X�J�[�\�����{�^���̏�Ńz�o�[�����ǂ���
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
#include "Image.h"
#include "DxLib.h"

Image::Image(const char* path):
	m_graphHandle(-1)
{
	if (path == "") {
		return;
	}

	//�t�@�C���p�X����摜�f�[�^�ǂݍ���
	m_graphHandle = LoadGraph(path);
	if (m_graphHandle == -1) {
		MessageBox(nullptr, "�摜�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "ERROR", MB_OK);
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

	//�A���t�@�u�����h���[�h�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255.0f));

	//�摜�f�[�^���ǂݍ��܂�Ă��Ȃ��Ȃ�A�}�`��`��
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
	//�摜�`��
	DrawExtendGraph(x, y, x + w, y + h, m_graphHandle, TRUE);

	//�u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

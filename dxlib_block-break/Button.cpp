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

	//�}�E�X�ʒu���擾
	Vec2 m = InputManager::GetMousePos();

	//�}�E�X�ʒu�̃{�^���͈͓�����
	if ((x < m.x && m.x < x + width) &&
		(y < m.y && m.y < y + height))
	{
		//�z�o�[���t���O�𗧂Ă�
		m_isHovered = true;
		//�z�o�[������
		m_img->SetColor(m_hoverColor[0], m_hoverColor[1], m_hoverColor[2]);

		//�}�E�X�{�^�����N���b�N����Ă�����A
		if (InputManager::GetKeyExit(KEY_ID::MOUSE_LEFT)) 
		{
			//�{�^�������t���O�𗧂Ă�
			m_isPushed = true;
			
			//�{�^������������
			m_onClick();
		}
	}
}

void Button::Render()
{
	//�{�^���摜��`��
	m_img->Render(x, y, width, height);

	//�{�^���e�L�X�g��`��
	m_txt->Render(x + 10, y + 10);
}

void Button::SetText(Text* txt)
{
	Release(m_txt);
	m_txt = txt;
}

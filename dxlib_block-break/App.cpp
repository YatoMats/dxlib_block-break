#include "App.h"
#include <Windows.h>

bool App::s_isPlaying = true;

int App::resolutionWidth = 720;
int App::resolutionHeight = 720;

const int App::fps = 60;

void App::PopUpQuitQuestion()
{
	//�}�E�X�J�[�\���\���ݒ�
	//SetMouseDispFlag(TRUE);
	
	//�I���m�F�E�B���h�E�\��
	if (IDYES == MessageBox(nullptr, TEXT("�A�v���P�[�V�������I�����܂����H"), TEXT("�m�F"), MB_YESNO)) {
		//YES���I�����ꂽ��A�A�v���P�[�V�����ғ����t���O��܂�
		s_isPlaying = false;
	}
	
	//�}�E�X�J�[�\���\���ݒ�
	//SetMouseDispFlag(FALSE);
}

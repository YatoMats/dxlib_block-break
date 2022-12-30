#include "DxLib.h"
#include <Windows.h>
#include <time.h>
#include "App.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "MainScene.h"
#include "TitleScene.h"
#include "ResultScene.h"

#pragma comment(lib,"winmm.lib")

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

int WINAPI WinMain
(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�����V�[�h�l�ݒ�
	srand((unsigned int)time(NULL));

	//�X�N���[���T�C�Y�̎擾
	int dispx = GetSystemMetrics(SM_CXSCREEN);
	int dispy = GetSystemMetrics(SM_CYSCREEN);
	
	//�E�B���h�E�𑜓x�ݒ�
	App::SetResolution(dispy - 95, dispy - 95);

	//�E�B���h�E���[�h�ύX
	ChangeWindowMode(true);
	//�E�B���h�E�j�����A�v�����ő���ł���悤��
	SetWindowUserCloseEnableFlag(false);
	// ��ʃT�C�Y�ݒ�
	SetGraphMode(App::GetResolutionWidth(), App::GetResolutionHeight(), 32);
	//�w�i�F�ݒ�
	SetBackgroundColor(123, 123, 123);
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	//�}�E�X�J�[�\���\���ݒ�
	//SetMouseDispFlag(FALSE);
	

	//���͏�񏉊���
	InputManager::Init();


	//�Q�[��������

	//�V�[���̃r���h�ݒ�
	SceneManager::RegisterSceneBuild("TitleScene", []() {return new TitleScene(); });
	SceneManager::RegisterSceneBuild("MainScene", []() {return new MainScene(); });
	SceneManager::RegisterSceneBuild("ResultScene", []() {return new ResultScene(); });

	//�ŏ��̃V�[��(TitleScene)�̓ǂݍ���
	if (!SceneManager::LoadScene(0)) return 0;


	//�t���[�����[�g�ݒ�
	//����\���ō��l��
	timeBeginPeriod(1);
	//�v���J�n����
	unsigned int startTime = timeGetTime();
	//1�t���[��������̃~���b����
	unsigned int mspf = 1000 / App::GetFrameRate();

	// ���C�����[�v
	while (ProcessMessage() == 0 && App::IsPlaying())
	{
		//�t���[�����[�g���킹����
		unsigned int elapsedTime = timeGetTime() - startTime;
		if (elapsedTime > mspf)
		{
			startTime = timeGetTime();

			//�E�B���h�E�~�{�^���N���b�N���ȂǁA�E�B���h�E�����쎞�A�܂��́AESC�L�[�������A
			if (GetWindowUserCloseFlag(TRUE) || InputManager::GetKeyEnter(KEY_ID::ESC) //|| GetKeyState(VK_ESCAPE) < 0
				) 
			{
				//�A�v���P�[�V�����I���m�F�E�B���h�E�\��
				App::PopUpQuitQuestion();
			}

			//���͏��X�V
			InputManager::Update();

			//�Q�[���V�[���̍X�V
			SceneManager::Update();

			// ��ʂ�����������
			ClearDrawScreen();

			//�Q�[���V�[���̕`��
			SceneManager::Render();

			// ����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();
		}
	}

	//�Q�[���I������
	SceneManager::Fin();

	DxLib::DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}
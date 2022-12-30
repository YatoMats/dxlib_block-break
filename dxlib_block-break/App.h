#pragma once

class App
{
	static bool s_isPlaying;

	static int resolutionWidth;
	static int resolutionHeight;
	static const int fps;
public:
	//�𑜓x��ݒ�
	static void SetResolution(int x, int y) { resolutionWidth = x; resolutionHeight = y; }

	//�E�B���h�E���𑜓x���擾
	static int GetResolutionWidth() { return resolutionWidth; }
	//�E�B���h�E�c�𑜓x���擾
	static int GetResolutionHeight() { return resolutionHeight; }

	//1�b������ɏ�������t���[�������擾
	static int GetFrameRate() { return fps; }


	//�A�v���P�[�V�������ғ�����
	static bool IsPlaying() { return s_isPlaying; }
	//�A�v���P�[�V�������I������
	static void Quit() { s_isPlaying = false; }

	//�{���ɏI�����邩���₷��|�b�v�A�b�v�E�B���h�E���o��
	static void PopUpQuitQuestion();
};
#include "InputManager.h"
#include "DxLib.h"

//#include <Xinput.h>
//#pragma comment (lib, "xinput.lib")

//���͏�ԏ�����
InputManager::InputState InputManager::s_inputStates[(int)KEY_ID::MAX_COUNT] = {
	InputManager::InputState::NOT_PUSHED
};
//�L�[�R�[�h�\������
int InputManager::s_keyCodes[(int)KEY_ID::MAX_COUNT] = {
	VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
	VK_ESCAPE, VK_RETURN, VK_BACK, VK_DELETE,
	VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT,
	VK_LSHIFT, VK_RSHIFT,
	VK_LCONTROL, VK_RCONTROL,
	VK_LMENU, VK_RMENU,
	VK_TAB, VK_SPACE,
	VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,
	VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,
	0x41, 0x42, 0x43, 0x44, 0x45,
	0x46, 0x47, 0x48, 0x49, 0x4a,
	0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54,
	0x55, 0x56, 0x57, 0x58, 0x59, 0x5a,
	'0','1','2','3','4','5','6','7','8','9',
};

Vec2 InputManager::s_mousePos;
int InputManager::s_mouseRot = 0;

//�p�b�h�{�^�����͏�ԏ�����
/*InputManager::InputState InputManager::s_padStates[(int)PAD_ID::MAX_COUNT] = {
	InputManager::InputState::NOT_PUSHED
};
//�p�b�h�{�^���̃R�[�h�\������
int InputManager::s_padCodes[(int)PAD_ID::MAX_COUNT] = {

	XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_DOWN, XINPUT_GAMEPAD_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_BACK, XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_LEFT_SHOULDER, XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB, XINPUT_GAMEPAD_RIGHT_THUMB
};*/

void InputManager::Init()
{
	//�}�E�X�J�[�\���ʒu��񏉊���
	int x, y;
	GetMousePoint(&x, &y);
	s_mousePos = Vec2((float)x, (float)y);
}

void InputManager::Update()
{
	//�}�E�X�J�[�\���ʒu���X�V
	int x, y;
	GetMousePoint(&x, &y);
	s_mousePos = Vec2((float)x, (float)y);

	//�}�E�X�z�C�[���̉�]�ʏ��X�V
	s_mouseRot = GetMouseWheelRotVol();

	//�L�[���͏�Ԃ̍X�V
	for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
		//���t���[���ŉ�����Ă��āA
		if (GetKeyState(s_keyCodes[i]) < 0) {
			//�O�t���[���ŉ�����Ă���Ȃ�A
			if (s_inputStates[i] == InputState::PUSHED_ENTER || s_inputStates[i] == InputState::PUSHED)
			{
				//������Ă���Œ��̏�Ԃ�
				s_inputStates[i] = InputState::PUSHED;
			}
			//�O�t���[���ŉ�����Ă��Ȃ��Ȃ�A
			else if (s_inputStates[i] == InputState::NOT_PUSHED) {
				//������n�߂̏�Ԃ�
				s_inputStates[i] = InputState::PUSHED_ENTER;
			}
		}
		//���t���[���ŉ�����Ă��炸�A
		else {
			//�O�t���[���ŉ�����Ă��Ȃ��Ȃ�A
			if (s_inputStates[i] == InputState::PUSHED_EXIT || s_inputStates[i] == InputState::NOT_PUSHED)
			{
				//������Ă��Ȃ���Ԃ�
				s_inputStates[i] = InputState::NOT_PUSHED;
			}
			//�O�t���[���ŉ�����Ă���Ȃ�A
			if (s_inputStates[i] == InputState::PUSHED || s_inputStates[i] == InputState::PUSHED_ENTER)
			{
				//������I����Ԃ�
				s_inputStates[i] = InputState::PUSHED_EXIT;
			}
		}
	}

	//�p�b�h���͏�Ԃ̍X�V
	/*_XINPUT_STATE state;
	ZeroMemory(&state, sizeof(_XINPUT_STATE));

	//�R���g���[���[�ڑ���Ԏ擾
	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		//�R���g���[���[�ڑ�������

		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++)
		{
			if (state.Gamepad.wButtons & s_padCodes[i])
			{
				s_padStates[i] = InputState::PUSHED;

				MessageBox(nullptr, TEXT("�p�b�h�{�^������"), TEXT(""), MB_OK);
			}
			else
			{
				s_padStates[i] = InputState::NOT_PUSHED;
			}
		}
	}*/
}

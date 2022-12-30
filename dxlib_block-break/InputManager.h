#pragma once
#include "Vec2.h"

enum class KEY_ID {
	MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE,
	ESC, ENTER, BACK, DEL,
	UP, DOWN, RIGHT, LEFT,
	SHIFT_LEFT, SHIFT_RIGHT,
	CTRL_LEFT, CTRL_RIGHT,
	ALT_LEFT, ALT_RIGHT,
	TAB, SPACE,
	F1, F2, F3, F4, F5, F6, 
	F7, F8, F9, F10, F11, F12,
	A, B, C, D, E,
	F, G, H, I, J,
	K, L, M, N, O,
	P, Q, R, S, T,
	U, V, W, X, Y, Z,
	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	MAX_COUNT
};

//�Q�[���p�b�h�̃{�^���̎���ID
/*enum class PAD_ID
{
	UP, DOWN, RIGHT, LEFT, 
	A, B, X, Y,
	BACK, START,
	L_SHOULDER, R_SHOULDER, 
	L_THUMB, R_THUMB, 
	MAX_COUNT
};*/

class InputManager {
	enum class InputState {
		//������Ă��Ȃ��A�����ꂽ�u�ԁA������Ă���A�����I���
		NOT_PUSHED, PUSHED_ENTER, PUSHED, PUSHED_EXIT
	};
	
	//�Q�[���Ŏg�����ׂẴL�[�̓��͏��
	static InputState s_inputStates[(int)KEY_ID::MAX_COUNT];
	//�L�[�R�[�h�\
	static int s_keyCodes[(int)KEY_ID::MAX_COUNT];

	//�X�N���[����̃}�E�X�J�[�\���ʒu
	static Vec2 s_mousePos;
	//�}�E�X�z�C�[���̉�]��
	static int s_mouseRot;


	//�Q�[���p�b�h�{�^���̓��͏��
	/*static InputState s_padStates[(int)PAD_ID::MAX_COUNT];
	//�Q�[���p�b�h�{�^���̃R�[�h�\
	static int s_padCodes[(int)PAD_ID::MAX_COUNT];
	//�Q�[���p�b�h�̍��E�X�e�B�b�N�̌X��
	static Vec2 s_padLStick;
	static Vec2 s_padRStick;*/

public:
	//���͏�ԏ�����
	static void Init();
	//���͏�ԍX�V
	static void Update();

	//�ΏۃL�[�������ꂽ�u�Ԃ��ǂ���
	static bool GetKeyEnter(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED_ENTER) return true;
		return false;
	}
	//�ΏۃL�[��������Ă���Œ���
	static bool GetKey(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED) return true;
		return false;
	}
	//�ΏۃL�[�������ꂽ�u�Ԃ�
	static bool GetKeyExit(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED_EXIT) return true;
		return false;
	}

	//�����ꂩ�̃L�[�������ꂽ�u�Ԃ�
	static bool GetAnyKeyEnter() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED_ENTER)return true;
		}
		return false;
	}
	//�����ꂩ�̃L�[��������Ă���Œ���
	static bool GetAnyKey() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED)return true;
		}
		return false;
	}
	//�����ꂩ�̃L�[�������ꂽ�u�Ԃ�
	static bool GetAnyKeyExit() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED_EXIT)return true;
		}
		return false;
	}

	//�X�N���[����̃}�E�X�J�[�\���̈ʒu���擾
	static Vec2 GetMousePos() { return s_mousePos; }
	//�}�E�X�z�C�[���̉�]�ʂ��擾
	static int GetMouseRot() { return s_mouseRot; }


	//�Ώۂ̃Q�[���p�b�h�{�^���������ꂽ�u�Ԃ��ǂ���
	/*static bool GetPadButtonEnter(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED_ENTER) return true;
		return false;
	}
	//�Ώۂ̃Q�[���p�b�h�{�^����������Ă���Œ���
	static bool GetPadButton(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED) return true;
		return false;
	}
	//�Ώۂ̃Q�[���p�b�h�{�^���������ꂽ�u�Ԃ�
	static bool GetPadButtonExit(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED_EXIT) return true;
		return false;
	}

	//�����ꂩ�̃L�[�������ꂽ�u�Ԃ�
	static bool GetAnyButtonEnter() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED_ENTER)return true;
		}
		return false;
	}
	//�����ꂩ�̃L�[��������Ă���Œ���
	static bool GetAnyButton() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED)return true;
		}
		return false;
	}
	//�����ꂩ�̃L�[�������ꂽ�u�Ԃ�
	static bool GetAnyButtonExit() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED_EXIT)return true;
		}
		return false;
	}

	//�Q�[���p�b�h�̍��X�e�B�b�N�̌X�����擾
	static Vec2 GetLStick() { return s_padLStick; }
	//�Q�[���p�b�h�̉E�X�e�B�b�N�̌X�����擾
	static Vec2 GetRStick() { return s_padRStick; }*/
};
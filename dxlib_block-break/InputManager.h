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

//ゲームパッドのボタンの識別ID
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
		//押されていない、押された瞬間、押されている、押し終わり
		NOT_PUSHED, PUSHED_ENTER, PUSHED, PUSHED_EXIT
	};
	
	//ゲームで使うすべてのキーの入力状態
	static InputState s_inputStates[(int)KEY_ID::MAX_COUNT];
	//キーコード表
	static int s_keyCodes[(int)KEY_ID::MAX_COUNT];

	//スクリーン上のマウスカーソル位置
	static Vec2 s_mousePos;
	//マウスホイールの回転量
	static int s_mouseRot;


	//ゲームパッドボタンの入力状態
	/*static InputState s_padStates[(int)PAD_ID::MAX_COUNT];
	//ゲームパッドボタンのコード表
	static int s_padCodes[(int)PAD_ID::MAX_COUNT];
	//ゲームパッドの左右スティックの傾き
	static Vec2 s_padLStick;
	static Vec2 s_padRStick;*/

public:
	//入力状態初期化
	static void Init();
	//入力状態更新
	static void Update();

	//対象キーが押された瞬間かどうか
	static bool GetKeyEnter(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED_ENTER) return true;
		return false;
	}
	//対象キーが押されている最中か
	static bool GetKey(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED) return true;
		return false;
	}
	//対象キーが離された瞬間か
	static bool GetKeyExit(KEY_ID key) {
		if (s_inputStates[(int)key] == InputState::PUSHED_EXIT) return true;
		return false;
	}

	//いずれかのキーが押された瞬間か
	static bool GetAnyKeyEnter() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED_ENTER)return true;
		}
		return false;
	}
	//いずれかのキーが押されている最中か
	static bool GetAnyKey() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED)return true;
		}
		return false;
	}
	//いずれかのキーが離された瞬間か
	static bool GetAnyKeyExit() {
		for (int i = 0; i < (int)KEY_ID::MAX_COUNT; i++) {
			if (s_inputStates[i] == InputState::PUSHED_EXIT)return true;
		}
		return false;
	}

	//スクリーン上のマウスカーソルの位置を取得
	static Vec2 GetMousePos() { return s_mousePos; }
	//マウスホイールの回転量を取得
	static int GetMouseRot() { return s_mouseRot; }


	//対象のゲームパッドボタンが押された瞬間かどうか
	/*static bool GetPadButtonEnter(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED_ENTER) return true;
		return false;
	}
	//対象のゲームパッドボタンが押されている最中か
	static bool GetPadButton(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED) return true;
		return false;
	}
	//対象のゲームパッドボタンが離された瞬間か
	static bool GetPadButtonExit(PAD_ID key) {
		if (s_padStates[(int)key] == InputState::PUSHED_EXIT) return true;
		return false;
	}

	//いずれかのキーが押された瞬間か
	static bool GetAnyButtonEnter() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED_ENTER)return true;
		}
		return false;
	}
	//いずれかのキーが押されている最中か
	static bool GetAnyButton() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED)return true;
		}
		return false;
	}
	//いずれかのキーが離された瞬間か
	static bool GetAnyButtonExit() {
		for (int i = 0; i < (int)PAD_ID::MAX_COUNT; i++) {
			if (s_padStates[i] == InputState::PUSHED_EXIT)return true;
		}
		return false;
	}

	//ゲームパッドの左スティックの傾きを取得
	static Vec2 GetLStick() { return s_padLStick; }
	//ゲームパッドの右スティックの傾きを取得
	static Vec2 GetRStick() { return s_padRStick; }*/
};
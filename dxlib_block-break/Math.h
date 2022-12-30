#pragma once
#include <random>

struct Math
{
	//�~����
	static const float PI;

	//���W�A���p����x���p��
	static float RadToDeg(float radian) {
		return radian * 180.0f / Math::PI;
	}
	//�x���p���烉�W�A���p��
	static float DegToRad(float degree) {
		return degree / 180.0f * Math::PI;
	}

	//������2���Ԃ�
	template<class Num>
	static Num Pow2(Num n) { return n * n; }

	//n �� p ���Ԃ�
	template<class Num>
	static Num Pow(Num n, Num p) {
		Num ret = 1;
		for (int i = 0; i < p; i++) {
			ret *= n;
		}
		return ret;
	}

	//min ���� max �܂ł͈͓̔��̗�����Ԃ�
	static int RandRange(int min, int max) {
		return rand() % (max + 1 - min) + min;
	}

	template<class Num>
	static Num Abs(Num n) {
		if (n < 0) n *= -1;
		return n;
	}
};

#pragma once
#include <random>

struct Math
{
	//円周率
	static const float PI;

	//ラジアン角から度数角へ
	static float RadToDeg(float radian) {
		return radian * 180.0f / Math::PI;
	}
	//度数角からラジアン角へ
	static float DegToRad(float degree) {
		return degree / 180.0f * Math::PI;
	}

	//引数の2乗を返す
	template<class Num>
	static Num Pow2(Num n) { return n * n; }

	//n の p 乗を返す
	template<class Num>
	static Num Pow(Num n, Num p) {
		Num ret = 1;
		for (int i = 0; i < p; i++) {
			ret *= n;
		}
		return ret;
	}

	//min から max までの範囲内の乱数を返す
	static int RandRange(int min, int max) {
		return rand() % (max + 1 - min) + min;
	}

	template<class Num>
	static Num Abs(Num n) {
		if (n < 0) n *= -1;
		return n;
	}
};

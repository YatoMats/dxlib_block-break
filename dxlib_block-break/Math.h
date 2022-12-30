#pragma once
#include <random>

struct Math
{
	//‰~ü—¦
	static const float PI;

	//ƒ‰ƒWƒAƒ“Šp‚©‚ç“x”Šp‚Ö
	static float RadToDeg(float radian) {
		return radian * 180.0f / Math::PI;
	}
	//“x”Šp‚©‚çƒ‰ƒWƒAƒ“Šp‚Ö
	static float DegToRad(float degree) {
		return degree / 180.0f * Math::PI;
	}

	//ˆø”‚Ì2æ‚ğ•Ô‚·
	template<class Num>
	static Num Pow2(Num n) { return n * n; }

	//n ‚Ì p æ‚ğ•Ô‚·
	template<class Num>
	static Num Pow(Num n, Num p) {
		Num ret = 1;
		for (int i = 0; i < p; i++) {
			ret *= n;
		}
		return ret;
	}

	//min ‚©‚ç max ‚Ü‚Å‚Ì”ÍˆÍ“à‚Ì—”‚ğ•Ô‚·
	static int RandRange(int min, int max) {
		return rand() % (max + 1 - min) + min;
	}

	template<class Num>
	static Num Abs(Num n) {
		if (n < 0) n *= -1;
		return n;
	}
};

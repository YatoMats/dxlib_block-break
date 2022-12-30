#pragma once
#include "Math.h"
#include <math.h>

struct Vec2 {
	float x;
	float y;

	Vec2(float _x = 0, float _y = 0) :x(_x), y(_y) { }

	Vec2 operator+(Vec2 v) {
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator-(Vec2 v) {
		return Vec2(x - v.x, y - v.y);
	}

	Vec2& operator+=(Vec2 v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator-=(Vec2 v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2 operator+(float n) {
		return Vec2(x + n, y + n);
	}
	Vec2 operator-(float n) {
		return Vec2(x - n, y - n);
	}
	Vec2 operator*(float n) {
		return Vec2(x * n, y * n);
	}
	Vec2 operator/(float n) {
		return Vec2(x / n, y / n);
	}

	Vec2& operator+=(float n) {
		x += n;
		y += n;
		return *this;
	}
	Vec2& operator-=(float n) {
		x += n;
		y += n;
		return *this;
	}
	Vec2& operator*=(float n) {
		x *= n;
		y *= n;
		return *this;
	}
	Vec2& operator/=(float n) {
		x /= n;
		y /= n;
		return *this;
	}

	//内積
	static float Inner(Vec2 v1, Vec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	//内積
	float Dot(Vec2 v) {
		return x * v.x + y * v.y;
	}
	//疑似外積 
	//(2つの2次元ベクトルを3次元ベクトルに変換し、それらのz成分を0と置いた場合の、外積のz成分を返す)
	static float Outer(Vec2 v1, Vec2 v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	//疑似外積 
	//(2つの2次元ベクトルを3次元ベクトルに変換し、それらのz成分を0と置いた場合の、外積のz成分を返す)
	float Cross(Vec2 v) {
		return x * v.y - y * v.x;
	}

	//2ベクトル間の距離の2乗
	static float DistancePow(Vec2 v1, Vec2 v2) {
		return Math::Pow2(v1.x - v2.x) + Math::Pow2(v1.y - v2.y);
	}
	//2ベクトル間の距離の2乗
	float DistancePow(Vec2 v) {
		return Math::Pow2(x - v.x) + Math::Pow2(y - v.y);
	}

	//2ベクトル間の距離
	static float Distance(Vec2 v1, Vec2 v2) {
		return sqrtf(Math::Pow2(v1.x - v2.x) + Math::Pow2(v1.y - v2.y));
	}
	//2ベクトル間の距離
	float Distance(Vec2 v) {
		return sqrtf(Math::Pow2(x - v.x) + Math::Pow2(y - v.y));
	}

	//ベクトルの大きさ
	static float Magnitude(Vec2 v) {
		return sqrtf(Math::Pow2(v.x) + Math::Pow2(v.y));
	}
	//ベクトルの大きさを取得
	float Magnitude() {
		return sqrtf(Math::Pow2(x) + Math::Pow2(y));
	}

	//正規化
	//(ベクトルの向きをそのままに、大きさを1に変えたベクトルを返す)
	static Vec2 Norm(Vec2 v) {
		float d = Magnitude(v);
		return Vec2(v.x / d, v.y / d);
	}
	//thisベクトルの正規化ベクトルを取得
	//(ベクトルの向きをそのままに、大きさを1に変えたベクトルを返す)
	Vec2 norm() {
		float d = Magnitude();
		return Vec2(x / d, y / d);
	}
	//thisベクトルを正規化ベクトルに変換
	Vec2 Normalize() {
		float d = Magnitude();
		Vec2 m = Vec2(x / d, y / d);
		*this = m;
		return m;
	}

	//法線ベクトルwに対する、thisの反射ベクトルを返す
	Vec2 reflect(Vec2 w) {
		//入射ベクトル
		Vec2 v = *this;
		//法線の正規化ベクトル(向き成分)
		Vec2 wNorm = w.norm();

		float minusvDotw = (v * -1.0f).Dot(wNorm);
		Vec2 p = wNorm * minusvDotw;

		//反射ベクトル == 入射ベクトル×2 p
		Vec2 r = v + p * 2.0f;
		return r;
	}
	//法線ベクトルwに対する、thisの反射ベクトルを計算し、代入
	Vec2 Reflect(Vec2 w) {
		//入射ベクトル
		Vec2 v = *this;
		//法線の正規化ベクトル(向き成分)
		Vec2 wNorm = w.norm();

		float minusvDotw = (v * -1.0f).Dot(wNorm);
		Vec2 p = wNorm * minusvDotw;

		//反射ベクトル == 入射ベクトル×2 p
		Vec2 r = v + p * 2.0f;
		*this = r;
		return r;
	}

	//thisベクトルを、degree°回転させたベクトルを取得
	Vec2 rot(float degree) {
		float rad = Math::DegToRad(degree);
		return Vec2(
			x * cosf(rad) - y * sinf(rad),
			x * sinf(rad) + y * cosf(rad)
		);
	}
	//thisベクトルをdegree°回転させる
	Vec2 Rotate(float degree) {
		float rad = Math::DegToRad(degree);
		Vec2 rot = Vec2(
			x * cosf(rad) - y * sinf(rad),
			x * sinf(rad) + y * cosf(rad)
		);
		*this = rot;
		return rot;
	}

	//this地点から目的地点への向きを計算
	Vec2 DirectionTo(Vec2 destination) {
		return (destination - *this);
	}
};
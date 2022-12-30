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

	//����
	static float Inner(Vec2 v1, Vec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	//����
	float Dot(Vec2 v) {
		return x * v.x + y * v.y;
	}
	//�^���O�� 
	//(2��2�����x�N�g����3�����x�N�g���ɕϊ����A������z������0�ƒu�����ꍇ�́A�O�ς�z������Ԃ�)
	static float Outer(Vec2 v1, Vec2 v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	//�^���O�� 
	//(2��2�����x�N�g����3�����x�N�g���ɕϊ����A������z������0�ƒu�����ꍇ�́A�O�ς�z������Ԃ�)
	float Cross(Vec2 v) {
		return x * v.y - y * v.x;
	}

	//2�x�N�g���Ԃ̋�����2��
	static float DistancePow(Vec2 v1, Vec2 v2) {
		return Math::Pow2(v1.x - v2.x) + Math::Pow2(v1.y - v2.y);
	}
	//2�x�N�g���Ԃ̋�����2��
	float DistancePow(Vec2 v) {
		return Math::Pow2(x - v.x) + Math::Pow2(y - v.y);
	}

	//2�x�N�g���Ԃ̋���
	static float Distance(Vec2 v1, Vec2 v2) {
		return sqrtf(Math::Pow2(v1.x - v2.x) + Math::Pow2(v1.y - v2.y));
	}
	//2�x�N�g���Ԃ̋���
	float Distance(Vec2 v) {
		return sqrtf(Math::Pow2(x - v.x) + Math::Pow2(y - v.y));
	}

	//�x�N�g���̑傫��
	static float Magnitude(Vec2 v) {
		return sqrtf(Math::Pow2(v.x) + Math::Pow2(v.y));
	}
	//�x�N�g���̑傫�����擾
	float Magnitude() {
		return sqrtf(Math::Pow2(x) + Math::Pow2(y));
	}

	//���K��
	//(�x�N�g���̌��������̂܂܂ɁA�傫����1�ɕς����x�N�g����Ԃ�)
	static Vec2 Norm(Vec2 v) {
		float d = Magnitude(v);
		return Vec2(v.x / d, v.y / d);
	}
	//this�x�N�g���̐��K���x�N�g�����擾
	//(�x�N�g���̌��������̂܂܂ɁA�傫����1�ɕς����x�N�g����Ԃ�)
	Vec2 norm() {
		float d = Magnitude();
		return Vec2(x / d, y / d);
	}
	//this�x�N�g���𐳋K���x�N�g���ɕϊ�
	Vec2 Normalize() {
		float d = Magnitude();
		Vec2 m = Vec2(x / d, y / d);
		*this = m;
		return m;
	}

	//�@���x�N�g��w�ɑ΂���Athis�̔��˃x�N�g����Ԃ�
	Vec2 reflect(Vec2 w) {
		//���˃x�N�g��
		Vec2 v = *this;
		//�@���̐��K���x�N�g��(��������)
		Vec2 wNorm = w.norm();

		float minusvDotw = (v * -1.0f).Dot(wNorm);
		Vec2 p = wNorm * minusvDotw;

		//���˃x�N�g�� == ���˃x�N�g���~2 p
		Vec2 r = v + p * 2.0f;
		return r;
	}
	//�@���x�N�g��w�ɑ΂���Athis�̔��˃x�N�g�����v�Z���A���
	Vec2 Reflect(Vec2 w) {
		//���˃x�N�g��
		Vec2 v = *this;
		//�@���̐��K���x�N�g��(��������)
		Vec2 wNorm = w.norm();

		float minusvDotw = (v * -1.0f).Dot(wNorm);
		Vec2 p = wNorm * minusvDotw;

		//���˃x�N�g�� == ���˃x�N�g���~2 p
		Vec2 r = v + p * 2.0f;
		*this = r;
		return r;
	}

	//this�x�N�g�����Adegree����]�������x�N�g�����擾
	Vec2 rot(float degree) {
		float rad = Math::DegToRad(degree);
		return Vec2(
			x * cosf(rad) - y * sinf(rad),
			x * sinf(rad) + y * cosf(rad)
		);
	}
	//this�x�N�g����degree����]������
	Vec2 Rotate(float degree) {
		float rad = Math::DegToRad(degree);
		Vec2 rot = Vec2(
			x * cosf(rad) - y * sinf(rad),
			x * sinf(rad) + y * cosf(rad)
		);
		*this = rot;
		return rot;
	}

	//this�n�_����ړI�n�_�ւ̌������v�Z
	Vec2 DirectionTo(Vec2 destination) {
		return (destination - *this);
	}
};
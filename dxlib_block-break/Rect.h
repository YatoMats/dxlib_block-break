#pragma once
#include "Vec2.h"

//��`���
class Rect {
	//����ʒu
	float x = 0.0f;
	float y = 0.0f;
	//��
	float w = 50.0f;
	//����
	float h = 50.0f;

	//����ʒu
	//Vec2 min;
	//�E���ʒu
	//Vec2 max;
	//����ʒu
	//Vec2 pos;
	//������
	//Vec2 size;
	//���S�ʒu
	//Vec2 center;

	/// <summary>
	/// ��`��񏉊��ݒ�
	/// </summary>
	/// <param name="_x">����x�ʒu���W</param>
	/// <param name="_y">����y�ʒu���W</param>
	/// <param name="_w">��</param>
	/// <param name="_h">����</param>
	Rect(float _x = 0, float _y = 0, float _w = 0, float _h = 0)
		//:x(_x), y(_y), w(_w), h(_h)
	{
		Set(_x, _y, _w, _h);
	}

	//��`�����o�ϐ����X�V
	void Set(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		//
	}
};
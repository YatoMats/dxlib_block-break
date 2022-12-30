#pragma once
#include "Rect.h"

//�����蔻��v�Z
struct Collision {

	/// <summary>
	/// �~���m�̓����蔻��
	/// </summary>
	/// <param name="p">�~1�̒��S�_</param>
	/// <param name="r">�~1�̔��a</param>
	/// <param name="p2">�~2�̒��S�_</param>
	/// <param name="r2">�~2�̔��a</param>
	/// <returns></returns>
	static bool CircleToCircle(Vec2 p, float r, Vec2 p2, float r2) 
	{
		//�����v�Z
		float dPow = p.DistancePow(p2);
		//�����蔻��v�Z
		if (dPow < Math::Pow2(r + r2)) 
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// �~�Ƌ�`�Ƃ̓����蔻��
	/// </summary>
	/// <param name="c">�~�̒��S�_</param>
	/// <param name="r">�~�̔��a</param>
	/// <param name="b">��`�̒��S�_</param>
	/// <param name="w">��`�̉���</param>
	/// <param name="h">��`�̍���(�c��)</param>
	/// <returns></returns>
	static bool CircleToBox(Vec2 c, float r, Vec2 b, float w, float h) 
	{
		//��`����
		Vec2 min = Vec2(b.x - w / 2, b.y - h / 2);
		//��`�E��
		Vec2 max = Vec2(b.x + w / 2, b.y + h / 2);

		//�����ɉ~�̔��a�̒l�𑫂�����`�ƁA�~�̒��S�_�Ƃ̓����蔻��
		if ((min.x - r < c.x && c.x < max.x + r) &&
			(min.y < c.y && c.y < min.y))
			return true;
		//�����ɉ~�̔��a�̒l�𑫂�����`�ƁA�~�̒��S�_�Ƃ̓����蔻��
		if ((min.x < c.x && c.x < max.x) &&
			(min.y - r < c.y && c.y < max.y + r))
			return true;

		//��`4���_�Ɖ~�Ƃ̓����蔻��
		if (c.DistancePow(min) < Math::Pow2(r)) return true;
		if (c.DistancePow(Vec2(min.x, max.y)) < Math::Pow2(r)) return true;
		if (c.DistancePow(Vec2(max.x, min.y)) < Math::Pow2(r)) return true;
		if (c.DistancePow(max) < Math::Pow2(r)) return true;

		return false;
	}

	/// <summary>
	/// ��`�Ƌ�`�Ƃ̓����蔻��
	/// </summary>
	/// <param name="p">��`1�̒��S�_</param>
	/// <param name="w">��`1�̉���</param>
	/// <param name="h">��`1�̍���(�c��)</param>
	/// <param name="p2">��`2�̒��S�_</param>
	/// <param name="w2">��`2�̉���</param>
	/// <param name="h2">��`2�̍���</param>
	/// <returns></returns>
	static bool BoxToBox(Vec2 p, float w, float h, Vec2 p2, float w2, float h2)
	{
		//��`1����
		Vec2 min = Vec2(p.x - w / 2, p.y - h / 2);
		//��`1�E��
		Vec2 max = Vec2(p.x + w / 2, p.y + h / 2);

		//��`2����
		Vec2 min2 = Vec2(p2.x - w2 / 2, p2.y - h2 / 2);
		//��`2�E��
		Vec2 max2 = Vec2(p2.x + w2 / 2, p2.y + h2 / 2);

		//��`��x�������������Ă��āAy�������������Ă���Ȃ�A�������Ă���
		if ((min.x < max2.x) && (max.x > min2.x) &&
			(min.y < max2.y) && (max.y > min2.y))
			return true;
		return false;

		if ((p.x < p2.x + w2) && (p.x + w > p2.x) &&
			(p.y < p2.y + h2) && (p.y + h > p2.y))
			return true;
		return false;
	}
};
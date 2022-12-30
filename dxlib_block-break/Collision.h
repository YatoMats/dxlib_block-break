#pragma once
#include "Rect.h"

//当たり判定計算
struct Collision {

	/// <summary>
	/// 円同士の当たり判定
	/// </summary>
	/// <param name="p">円1の中心点</param>
	/// <param name="r">円1の半径</param>
	/// <param name="p2">円2の中心点</param>
	/// <param name="r2">円2の半径</param>
	/// <returns></returns>
	static bool CircleToCircle(Vec2 p, float r, Vec2 p2, float r2) 
	{
		//距離計算
		float dPow = p.DistancePow(p2);
		//当たり判定計算
		if (dPow < Math::Pow2(r + r2)) 
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// 円と矩形との当たり判定
	/// </summary>
	/// <param name="c">円の中心点</param>
	/// <param name="r">円の半径</param>
	/// <param name="b">矩形の中心点</param>
	/// <param name="w">矩形の横幅</param>
	/// <param name="h">矩形の高さ(縦幅)</param>
	/// <returns></returns>
	static bool CircleToBox(Vec2 c, float r, Vec2 b, float w, float h) 
	{
		//矩形左上
		Vec2 min = Vec2(b.x - w / 2, b.y - h / 2);
		//矩形右下
		Vec2 max = Vec2(b.x + w / 2, b.y + h / 2);

		//横幅に円の半径の値を足した矩形と、円の中心点との当たり判定
		if ((min.x - r < c.x && c.x < max.x + r) &&
			(min.y < c.y && c.y < min.y))
			return true;
		//高さに円の半径の値を足した矩形と、円の中心点との当たり判定
		if ((min.x < c.x && c.x < max.x) &&
			(min.y - r < c.y && c.y < max.y + r))
			return true;

		//矩形4頂点と円との当たり判定
		if (c.DistancePow(min) < Math::Pow2(r)) return true;
		if (c.DistancePow(Vec2(min.x, max.y)) < Math::Pow2(r)) return true;
		if (c.DistancePow(Vec2(max.x, min.y)) < Math::Pow2(r)) return true;
		if (c.DistancePow(max) < Math::Pow2(r)) return true;

		return false;
	}

	/// <summary>
	/// 矩形と矩形との当たり判定
	/// </summary>
	/// <param name="p">矩形1の中心点</param>
	/// <param name="w">矩形1の横幅</param>
	/// <param name="h">矩形1の高さ(縦幅)</param>
	/// <param name="p2">矩形2の中心点</param>
	/// <param name="w2">矩形2の横幅</param>
	/// <param name="h2">矩形2の高さ</param>
	/// <returns></returns>
	static bool BoxToBox(Vec2 p, float w, float h, Vec2 p2, float w2, float h2)
	{
		//矩形1左上
		Vec2 min = Vec2(p.x - w / 2, p.y - h / 2);
		//矩形1右下
		Vec2 max = Vec2(p.x + w / 2, p.y + h / 2);

		//矩形2左上
		Vec2 min2 = Vec2(p2.x - w2 / 2, p2.y - h2 / 2);
		//矩形2右下
		Vec2 max2 = Vec2(p2.x + w2 / 2, p2.y + h2 / 2);

		//矩形のx成分が交差していて、y成分も交差しているなら、当たっている
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
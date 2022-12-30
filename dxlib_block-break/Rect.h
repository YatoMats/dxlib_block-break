#pragma once
#include "Vec2.h"

//矩形情報
class Rect {
	//左上位置
	float x = 0.0f;
	float y = 0.0f;
	//幅
	float w = 50.0f;
	//高さ
	float h = 50.0f;

	//左上位置
	//Vec2 min;
	//右下位置
	//Vec2 max;
	//左上位置
	//Vec2 pos;
	//幅高さ
	//Vec2 size;
	//中心位置
	//Vec2 center;

	/// <summary>
	/// 矩形情報初期設定
	/// </summary>
	/// <param name="_x">左上x位置座標</param>
	/// <param name="_y">左上y位置座標</param>
	/// <param name="_w">幅</param>
	/// <param name="_h">高さ</param>
	Rect(float _x = 0, float _y = 0, float _w = 0, float _h = 0)
		//:x(_x), y(_y), w(_w), h(_h)
	{
		Set(_x, _y, _w, _h);
	}

	//矩形メンバ変数を更新
	void Set(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		//
	}
};
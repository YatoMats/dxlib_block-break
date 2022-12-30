#pragma once
#include "Vec2.h"

class Image;

class Actor {
public:
	bool isDestroyed = false;

	Vec2 pos = Vec2(0, 0);
	Vec2 size = Vec2(50, 50);
private:
	Image* m_img;
public:
	Actor(Image* img, float x = 0, float y = 0, float w = 100, float h = 100)
		:m_img(img), pos(x, y), size(w, h)
	{ }

	virtual ~Actor();

	void Render();

	Image* GetImage() { return m_img; }
};

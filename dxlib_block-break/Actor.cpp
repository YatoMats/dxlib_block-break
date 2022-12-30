#include "Actor.h"
#include "Image.h"

#ifndef Release
#define Release(x) if(x!=nullptr){delete x; x=nullptr;}
#endif // !Release

Actor::~Actor()
{
	Release(m_img);
}

void Actor::Render() 
{
	//アクター画像描画
	m_img->Render(
		(int)(pos.x - size.x / 2.0f),
		(int)(pos.y - size.y / 2.0f),
		(int)size.x,
		(int)size.y
	);

	/*if (shape == Shape::Box) {
		m_img->Render(
			(int)(pos.x - size.x / 2.0f), 
			(int)(pos.y - size.y / 2.0f),
			(int)size.x,
			(int)size.y
		);
	}
	else if (shape == Shape::Circle) {
		m_img->Render(
			(int)pos.x,
			(int)pos.y,
			(int)size.x,
			(int)size.y
		);
	}*/
}

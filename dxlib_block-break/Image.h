#pragma once

enum class Shape {
	Circle, Box
};

class Image {
	int m_graphHandle;

	//}Œ`•`‰æ‚ÌF
	float m_color[3] = { 1.0f,1.0f,1.0f };
public:
	//}Œ`•`‰æ‚ÌŒ`
	Shape shape = Shape::Box;

	//“§–¾“x
	float alpha = 1.0f;
public:
	Image(const char* path);
	~Image();
	
	void Render(int x, int y, int w, int h);

	void SetColor(float red, float green, float blue)
	{
		m_color[0] = red;
		m_color[1] = green;
		m_color[2] = blue;
	}
};
#pragma once

class Image;
class Text;
class Button;
class Audio;
class SceneFadeOuter;

class Panel 
{
public:
	bool isActive = false;
private:
	Image* m_img;

	Text* m_titleTxt;
	Text* m_descTxt;

	Button* m_button0;
	Button* m_button1;
	Button* m_button2;

	Audio* m_decisionSE;

	SceneFadeOuter* m_fadeOuter;

public:
	Panel();
	~Panel();
	void Update();
	void Render();
};
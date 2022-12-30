#include "Camera.h"
#include "DxLib.h"

void Camera::SetBackGroundColor(float red, float green, float blue)
{
	int r = (int)(red * 255.0f);
	int g = (int)(green * 255.0f);
	int b = (int)(blue * 255.0f);
	SetBackgroundColor(r, g, b);
}

#include "stdafx.h"
#include "Text.h"
#include "define.h"
#include "ResourceManager.h"

Text::Text(std::string text, GLint shaderId, GLint fontId, TEXT_COLOR color, float posX, float posY, float size,
	std::string text2, std::string text3)
{
	
	m_text = text;
	m_text2 = text2;
	m_text3 = text3;
	m_shaderId = shaderId;
	m_fontId = fontId;
	m_Color = EnumToVector(color);

	Set2DPosition(posX, posY);

	m_scale = Vector2(size, size);
}

Text::~Text() 
{
	
}




Vector4 Text::EnumToVector(TEXT_COLOR color)
{
	Vector4 vecColor;
	switch (color)
	{
	case TEXT_COLOR::WHILE:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::RED:
		vecColor = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::GREEN:
		vecColor = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::BLUE:
		vecColor = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::YELLOW:
		vecColor = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case TEXT_COLOR::PURPLE:
		vecColor = Vector4(0.5f, 0.0f, 1.0f, 1.0f);
		break;
	case TEXT_COLOR::CYAN:
		vecColor = Vector4(0.0f, 0.9f, 0.9f, 1.0f);
		break;
	default:
		vecColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	return vecColor;
}

void Text::Set2DPosition(GLfloat width, GLfloat height)
{
	m_Vec2DPos.x = width;
	m_Vec2DPos.y = height;

	float xx = (2.0 * m_Vec2DPos.x) / SCREEN_W - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / SCREEN_H;
	m_Vec3Position = Vector3(xx, yy, 1.0);
}

void Text::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

	float xx = (2.0 * m_Vec2DPos.x) / SCREEN_W - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / SCREEN_H;
	m_Vec3Position = Vector3(xx, yy, 1.0);
}




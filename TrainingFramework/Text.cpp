#include "stdafx.h"
#include "Text.h"
#include "define.h"
#include "ResourceManager.h"

Text::Text(std::string text, GLint shaderId, GLint fontId, TEXT_COLOR color, float posX, float posY, float size, TEXT_ALIGN align)
{
	
	m_text = text;
	m_shaderId = shaderId;
	m_fontId = fontId;
	m_Color = EnumToVector(color);
	m_Align = align;

	m_Vec2DPos.x = posX;
	m_Vec2DPos.y = posY;

	switch (m_Align) {
	case TEXT_ALIGN::LEFT:
		Set2DPosition(m_Vec2DPos.x, m_Vec2DPos.y);
		break;
	case TEXT_ALIGN::CENTER:
		Set2DPosition(m_Vec2DPos.x - getWidth() / 2, m_Vec2DPos.y);
		break;
	case TEXT_ALIGN::RIGHT:
		Set2DPosition(m_Vec2DPos.x - getWidth(), m_Vec2DPos.y);
		break;
	}

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
	float xx = (2.0 * width) / SCREEN_W - 1.0;
	float yy = 1.0 - (2.0 * height) / SCREEN_H;
	m_Vec3Position = Vector3(xx, yy, 1.0);
}

void Text::Set2DPosition(Vector2 pos)
{
	float xx = (2.0 * pos.x) / SCREEN_W - 1.0;
	float yy = 1.0 - (2.0 * pos.y) / SCREEN_H;
	m_Vec3Position = Vector3(xx, yy, 1.0);
}

unsigned int Text::getWidth() {
	switch (m_fontId) {
	case FONT_BANK:
		return m_text.size() * 16;
	case FONT_DOGICA:
	case FONT_DOGICA_BOLD:
		return m_text.size() * 22;
	default:
		return m_text.size() * 16;
	}
}

void Text::setText(std::string text) {
	m_text = text;

	switch (m_Align) {
	case TEXT_ALIGN::LEFT:
		break;
	case TEXT_ALIGN::CENTER:
		Set2DPosition(m_Vec2DPos.x - getWidth() / 2, m_Vec2DPos.y);
		break;
	case TEXT_ALIGN::RIGHT:
		Set2DPosition(m_Vec2DPos.x - getWidth(), m_Vec2DPos.y);
		break;
	}
}

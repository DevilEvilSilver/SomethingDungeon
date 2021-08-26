#pragma once
#include<string>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Shaders.h"
#include "Font.h"
 

enum class TEXT_COLOR {
	WHILE = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN,
	BLACK
};

enum class TEXT_ALIGN {
	LEFT = 0,
	CENTER,
	RIGHT
};

class Text {
private:

	Vector2	m_scale;
	GLint m_shaderId;
	GLint m_fontId;


public:
	std::string		m_text;
	Vector4			m_Color;
	TEXT_ALIGN		m_Align;
	Vector2 m_Vec2DPos;
	Vector3 m_Vec3Position;


	Text() {}
	Text(std::string text, GLint shaderId, GLint fontId, TEXT_COLOR color, float posX, float posY, float size, TEXT_ALIGN align = TEXT_ALIGN::LEFT);
	~Text();
	

	void Init() {}
	void cleanUp() {}

	Vector4 EnumToVector(TEXT_COLOR color);
	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);


	
	Vector4 getColor() { return m_Color; }
	Vector2 getScale() { return m_scale; }
	std::string		getText() { return m_text; }
	unsigned int getWidth();
	GLint getShaderId() { return m_shaderId; }
	GLint getFontId() { return m_fontId; }

	void setText(std::string text);
	void setColor(TEXT_COLOR color) { m_Color = EnumToVector(color); }
	void setScale(Vector2 scale) { m_scale = scale; }
};


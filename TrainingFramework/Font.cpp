#pragma once
#include "stdafx.h"
#include "Font.h"
#include "define.h"

Font::~Font()
{
	for (unsigned char c = 0; c < 128; c++) {
		glDeleteTextures(1, &m_Glyphs.at(c).TextureID);
	}
	glDeleteTextures(1, &_iTextID);

	FT_Done_FreeType(m_library);
}

Font::Font(unsigned int resourceID, const std::string& font)
{
	m_iResourceID = resourceID;
	initWithFiles(font);
}

bool Font::initWithFiles(const std::string& font)
{
	std::string _font = font;
	if (FT_Init_FreeType(&m_library))
	{
		printf("Could not init freetype library\n");
		return false;
	}

	if (FT_New_Face(m_library, _font.c_str(), 0, &m_face)) {
		printf("Could not open font \n");
		return false;
	}

	FT_Set_Pixel_Sizes(m_face, 0, 48);
	m_glyphSlot = m_face->glyph;

	glGenTextures(1, &_iTextID);
	glBindTexture(GL_TEXTURE_2D, _iTextID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &_vboId);

	FT_GlyphSlot glyphSlot = getFtGlyph();
	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(getFtFace(), c, FT_LOAD_RENDER))
		{
			continue;
		}
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyphSlot->bitmap.width,
			glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyphSlot->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//store glyph
		Glyph glyph = {
		texture,
		Vector2(glyphSlot->bitmap.width, glyphSlot->bitmap.rows),
		Vector2(glyphSlot->bitmap_left, glyphSlot->bitmap_top),
		glyphSlot->advance.x,
		glyphSlot->advance.y
		};
		m_Glyphs.insert(std::pair<char, Glyph>(c, glyph));
	}

	return true;
}


GLuint Font::getTextFontAdd()
{
	return _iTextID;
}

GLuint Font::getArrBuffer()
{
	return _vboId;
}

FT_Face Font::getFtFace() {
	return m_face;
}

FT_GlyphSlot Font::getFtGlyph() {
	return m_glyphSlot;
}
#pragma once
#include "stdafx.h"
#include "Font.h"
#include "define.h"

Font::~Font()
{
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
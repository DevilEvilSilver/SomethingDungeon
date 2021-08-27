#pragma once

#include <string>
#include <map>
#include "../Utilities/utilities.h"
#include "Glyph.h"
#include "ft2build.h"
#include FT_FREETYPE_H


class Font
{
private:

	GLuint		_vboId;
	GLuint		_iTextID;

	FT_Library			m_library;
	FT_Face				m_face;
	FT_GlyphSlot		m_glyphSlot;


public:
	unsigned int m_iResourceID;
	std::map<char, Glyph> m_Glyphs;

	~Font();

	Font(unsigned int resourceID,const std::string& font);
	bool		initWithFiles(const std::string& font);
	GLuint		getTextFontAdd();
	GLuint		getArrBuffer();
	FT_Face		getFtFace();
	FT_GlyphSlot getFtGlyph();

	



};

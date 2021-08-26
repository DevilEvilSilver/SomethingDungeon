#pragma once
#include "../Utilities/Math.h"

struct Glyph {
	unsigned int TextureID;		// ID handle of the glyph texture
	Vector2   Size;				// Size of glyph
	Vector2   Bearing;			// Offset from baseline to left/top of glyph
	unsigned int AdvanceX;		// Offset to advance to next glyph
	unsigned int AdvanceY;		// Offset to advance to next glyph
};
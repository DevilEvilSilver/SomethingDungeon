#pragma once

#include <GLES2/gl2.h>
#include <vector>
#include <string>

class TextureCube
{
public:
	GLuint m_RendererID;

	TextureCube();
	TextureCube(std::vector<std::string> file, GLint tiling);
	~TextureCube();

	void Bind(unsigned int slot = 0);
	void Unbind();
};
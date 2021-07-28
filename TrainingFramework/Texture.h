#pragma once

#include <GLES2/gl2.h>

class Texture
{
public:
	GLuint m_RendererID;
	GLint m_iWidth;
	GLint m_iHeight;
	GLint m_iBpp;

	Texture();
	Texture(const char* file, GLint tiling);
	~Texture();

	void Bind(unsigned int slot = 0);
	void Unbind();
};
#pragma once

#include <GLES2/gl2.h>

class Texture2D
{
public:
	GLuint m_RendererID;
	GLint m_iWidth;
	GLint m_iHeight;
	GLint m_iBpp;

	Texture2D();
	Texture2D(const char* file, GLint tiling);
	~Texture2D();

	void Bind(unsigned int slot = 0);
	void Unbind();
};
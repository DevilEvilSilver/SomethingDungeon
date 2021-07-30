#pragma once

#include <GLES2/gl2.h>

class Frame
{
public:
	unsigned int m_iResourceID;
	float m_fSPF;
	GLuint m_RendererID;
	GLint m_iWidth;
	GLint m_iHeight;
	GLint m_iBpp;

	Frame();
	Frame(unsigned int resourceID, const char* file, GLint tiling, float SPF = 0.0f);
	~Frame();

	void Bind(unsigned int slot = 0);
	void Unbind();
};
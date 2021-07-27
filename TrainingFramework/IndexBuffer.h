#pragma once

#include <GLES2/gl2.h>

class IndexBuffer
{
public:
	GLuint m_RendererID;
	GLuint m_Count;

	IndexBuffer();
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();
};
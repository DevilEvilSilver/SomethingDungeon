#pragma once

#include <GLES2/gl2.h>
#include "../Utilities/Math.h"

class VertexBuffer 
{
public:
	GLuint m_RendererID;

	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};
#pragma once

#include <GLES2/gl2.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Model
{
public:
	VertexBuffer *m_VertexBuffer;
	IndexBuffer *m_IndexBuffer;

	Model();
	Model(const void* vertexData, unsigned int vertexSize, const void* indexData, unsigned int indexCount);
	~Model();

	void Bind();
	void Unbind();
};
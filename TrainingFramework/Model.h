#pragma once

#include <GLES2/gl2.h>

class Model
{
public:
	unsigned int m_iResourceID;
	GLuint m_VertexRendererID;
	GLuint m_IndexRendererID;
	GLuint m_IndexCount;

	Model();
	Model(unsigned int resourceID, const void* vertexData, unsigned int vertexSize, const void* indexData, unsigned int indexCount);
	~Model();

	void Bind();
	void Unbind();
};
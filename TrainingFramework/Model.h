#pragma once

#include <GLES2/gl2.h>

class Model
{
public:
	GLuint m_VertexRendererID;
	GLuint m_IndexRendererID;
	GLuint m_Count;

	Model();
	Model(const void* vertexData, unsigned int vertexSize, const void* indexData, unsigned int indexCount);
	~Model();

	void Bind();
	void Unbind();
};
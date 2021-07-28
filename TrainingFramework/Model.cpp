#include <stdafx.h>
#include "Model.h"

Model::Model() {

}

Model::Model(const void* vertexData, unsigned int vertexSize, const void* indexData, unsigned int indexCount) 
	: m_Count(indexCount) {
	glGenBuffers(1, &m_VertexRendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexRendererID);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IndexRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexRendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

Model::~Model() {
	glDeleteBuffers(1, &m_VertexRendererID);
	glDeleteBuffers(1, &m_IndexRendererID);
}

void Model::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexRendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexRendererID);
}

void Model::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

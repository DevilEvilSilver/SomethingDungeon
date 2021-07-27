#include <stdafx.h>
#include "Model.h"

Model::Model() {

}

Model::Model(const void* vertexData, unsigned int vertexSize, const void* indexData, unsigned int indexCount) {
	m_VertexBuffer = new VertexBuffer(vertexData, vertexSize);
	m_IndexBuffer = new IndexBuffer(indexData, indexCount);
}

Model::~Model() {
	delete m_VertexBuffer;
	delete m_IndexBuffer;
}

void Model::Bind() {
	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();
}

void Model::Unbind() {
	m_VertexBuffer->Unbind();
	m_IndexBuffer->Unbind();
}

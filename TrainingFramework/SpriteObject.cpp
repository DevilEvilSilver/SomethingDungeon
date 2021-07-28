#include "stdafx.h"
#include "SpriteObject.h"
#include "Renderer.h"
#include "Vertex.h"

SpriteObject::SpriteObject() {}

SpriteObject::SpriteObject(unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
	GLfloat width, GLfloat height)
	: Object(shaderID, translationMatrix, rotationMatrix, scaleMatrix), m_fWidth(width), m_fHeight(height), 
	m_strState("mainIdleLeft"), m_fCurrFrameTime(0.0f), m_iCurrFrameIndex(0) {
	Vertex *vertices = new Vertex[4];

	vertices[0].pos.x = 0.0f; vertices[0].pos.y = -height; vertices[0].pos.z = 0.0f;
	vertices[0].uv.x = 0.0f; vertices[0].uv.y = 0.0f;
	vertices[1].pos.x = 0.0f; vertices[1].pos.y = 0.0f; vertices[1].pos.z = 0.0f;
	vertices[1].uv.x = 0.0f; vertices[1].uv.y = 1.0f;
	vertices[2].pos.x = -width; vertices[2].pos.y = 0.0f; vertices[2].pos.z = 0.0f;
	vertices[2].uv.x = 1.0f; vertices[2].uv.y = 1.0f;
	vertices[3].pos.x = -width; vertices[3].pos.y = -height; vertices[3].pos.z = 0.0f;
	vertices[3].uv.x = 1.0f; vertices[3].uv.y = 0.0f;

	GLuint *indices = new GLuint[6];

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	m_Model = new Model(0, vertices, sizeof(Vertex) * 4, indices, 6);
	delete[]vertices;
	delete[]indices;
}

SpriteObject::~SpriteObject() {
	delete m_Model;
}

void SpriteObject::Update(float frameTime) { 
	m_fCurrFrameTime += frameTime;
}

void SpriteObject::Render(Camera *camera) {
	Renderer::GetInstance()->DrawSprite(this, camera);
}
#include "stdafx.h"
#include "StaticObject.h"
#include "Renderer.h"

StaticObject::StaticObject() {}

StaticObject::StaticObject(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
	unsigned int type, float posX, float posY, float width, float height, float radius, std::vector<unsigned int> textureID, GLfloat textureScale)
	: Object(modelID, shaderID, translationMatrix, rotationMatrix, scaleMatrix, type, posX, posY, width, height, radius), m_fTextureScale(textureScale) {
	for (auto& obj : textureID) {
		m_iTextureID.push_back(obj);
	}
}

StaticObject::~StaticObject() {
	m_iTextureID.resize(0);
}

void StaticObject::Update(float frameTime) { }

void StaticObject::Render(Camera *camera) {
	Renderer::GetInstance()->DrawStatic(this, camera);
}

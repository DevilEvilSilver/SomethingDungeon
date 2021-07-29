#include "stdafx.h"
#include "Terrain.h"
#include "Renderer.h"

Terrain::Terrain() {}

Terrain::Terrain(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, 
	std::vector<unsigned int> textureID, GLfloat textureScale)
	: Object(modelID, shaderID, translationMatrix, rotationMatrix, scaleMatrix), m_fTextureScale(textureScale) {
	for (auto& obj : textureID) {
		m_iTextureID.push_back(obj);
	}
}

Terrain::~Terrain() {
	m_iTextureID.resize(0);
}

void Terrain::Update(float frameTime) { }

void Terrain::Render(Camera *camera) {
	Renderer::GetInstance()->DrawTerrain(this, camera);
}

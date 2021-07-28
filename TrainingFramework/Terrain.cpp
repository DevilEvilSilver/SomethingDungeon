#include "stdafx.h"
#include "Terrain.h"
#include "Renderer.h"

Terrain::Terrain() {}

Terrain::Terrain(unsigned int modelID, unsigned int shaderID, Matrix translationMatrix, Matrix rotationMatrix, Matrix scaleMatrix, GLfloat textureScale)
	: Object(shaderID, translationMatrix, rotationMatrix, scaleMatrix), m_iModelID(modelID), m_fTextureScale(textureScale) {
	
}

Terrain::~Terrain() {
	m_iTexture2DID.resize(0);
}

void Terrain::Update(float frameTime) { }

void Terrain::Render(Camera *camera) {
	Renderer::GetInstance()->DrawTerrain(this, camera);
}

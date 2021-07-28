#include "stdafx.h"
#include "Terrain.h"
#include "Renderer.h"

Terrain::Terrain() {}

Terrain::Terrain(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix, GLfloat textureScale)
	: Object(modelID, shaderID, worldMatrix), m_fTextureScale(textureScale) {
	
}

Terrain::~Terrain() {

}

void Terrain::Update(float frameTime) { }

void Terrain::Render(Camera *camera) {
	Renderer::GetInstance()->DrawTerrain(this, camera);
}

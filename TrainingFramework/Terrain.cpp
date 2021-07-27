#include "stdafx.h"
#include "Terrain.h"
#include "Renderer.h"

Terrain::Terrain() {}

Terrain::Terrain(unsigned int modelID, unsigned int shaderID, Matrix worldMatrix, float fogStart, float fogLength, Vector3 fogColor)
	: Object(modelID, shaderID, worldMatrix), m_fFogStart(fogStart), m_fFogLength(fogLength), m_FogColor(fogColor) {
	
}

Terrain::~Terrain() {

}

void Terrain::Update(float frameTime) { }

void Terrain::Render(Camera *camera) {
	Renderer::GetInstance()->DrawTerrain(this, camera);
}

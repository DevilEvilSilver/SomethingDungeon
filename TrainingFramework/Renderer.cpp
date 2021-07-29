#include "stdafx.h"
#include <GLES2/gl2.h>
#include "Renderer.h"
#include "define.h"
#include "ResourceManager.h"

Renderer * Renderer::s_Instance = NULL;

template <class T>
T GetResource(unsigned int id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (id == obj->m_iResourceID)
			return obj;
	}
	return 0;
}

template <class T>
T GetResource(std::string id, std::vector<T> objList) {
	for (auto&obj : objList) {
		if (!strcmp(id.c_str(), obj->m_strResourceID.c_str()))
			return obj;
	}
	return 0;
}

Renderer::Renderer(void) {
	this->Init();
}

Renderer::~Renderer() {

}

Renderer* Renderer::GetInstance()
{
	if (!s_Instance)
		s_Instance = new Renderer();
	return s_Instance;
}

void Renderer::ResetInstance() {
	delete s_Instance;
	s_Instance = NULL;
}

void Renderer::Init() {
	
}

void Renderer::DrawSprite(SpriteObject *sprite, Camera *camera) {
	Model *model = GetResource(sprite->m_iModelID, ResourceManager::GetInstance()->m_ModelList);
	Shaders *shader = GetResource(sprite->m_iShaderID, ResourceManager::GetInstance()->m_ShaderList);
	Animation *animation = GetResource(sprite->m_strState, ResourceManager::GetInstance()->m_AnimationList);

	shader->Bind();
	model->Bind();
	if (sprite->m_fCurrFrameTime >= animation->m_FrameList[sprite->m_iCurrFrameIndex]->m_fSPF) {
		sprite->m_iCurrFrameIndex = (sprite->m_iCurrFrameIndex + 1) % animation->m_FrameList.size();
		sprite->m_fCurrFrameTime = 0.0f;
	}
	animation->m_FrameList[sprite->m_iCurrFrameIndex]->Bind();

	Matrix wvpMatrix = sprite->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	//Set uniform
	glUniform1i(shader->texture2DUniform, 0);
	glUniformMatrix4fv(shader->wvpUniform, 1, GL_FALSE, (const GLfloat*)wvpMatrix.m);

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)VERTEX_OFFSET_POS);
	}
	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)VERTEX_OFFSET_UV);
	}

	glDrawElements(GL_TRIANGLES, model->m_IndexCount, GL_UNSIGNED_INT, 0);

	model->Unbind();
	animation->m_FrameList[sprite->m_iCurrFrameIndex]->Unbind();
	shader->Unbind();
}

void Renderer::DrawTerrain(Terrain *terrain, Camera *camera) {
	Model *model = GetResource(terrain->m_iModelID, ResourceManager::GetInstance()->m_ModelList);
	Shaders *shader = GetResource(terrain->m_iShaderID, ResourceManager::GetInstance()->m_ShaderList);

	shader->Bind();
	model->Bind();
	for (unsigned int i = 0; i < terrain->m_iTextureID.size(); i++) {
		GetResource(terrain->m_iTextureID[i], ResourceManager::GetInstance()->m_TextureList)->Bind(i);
	}

	Matrix wvpMatrix = terrain->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	//Set uniform
	glUniform1i(shader->texture2DUniform, 0);
	glUniform1i(shader->texture2DUniform2, 1);
	glUniform1i(shader->texture2DUniform3, 2);
	glUniform1i(shader->texture2DUniform4, 3);
	glUniform1f(shader->textureScaleUniform, terrain->m_fTextureScale);
	glUniformMatrix4fv(shader->wvpUniform, 1, GL_FALSE, (const GLfloat*)wvpMatrix.m);

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)VERTEX_OFFSET_POS);
	}
	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)VERTEX_OFFSET_UV);
	}

	glDrawElements(GL_TRIANGLES, model->m_IndexCount, GL_UNSIGNED_INT, 0);

	model->Unbind();
	for (unsigned int i = 0; i < terrain->m_iTextureID.size(); i++) {
		GetResource(terrain->m_iTextureID[i], ResourceManager::GetInstance()->m_TextureList)->Unbind();
	}
	shader->Unbind();
}
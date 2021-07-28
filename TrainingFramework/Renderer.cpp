#include "stdafx.h"
#include <GLES2/gl2.h>
#include "Renderer.h"
#include "define.h"
#include "ResourceManager.h"

Renderer * Renderer::s_Instance = NULL;

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

void Renderer::DrawTexture2D(Object *object, Camera *camera) {
	Model *model = ResourceManager::GetInstance()->m_ModelList[object->m_iModelID];
	Shaders *shader = ResourceManager::GetInstance()->m_ShaderList[object->m_iShaderID];

	shader->Bind();
	model->Bind();
	for (unsigned int i = 0; i < object->m_iTexture2DID.size(); i++) {
		ResourceManager::GetInstance()->m_Texture2DList[object->m_iTexture2DID[i]]->Bind(i);
	}
	
	Matrix wvpMatrix = object->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	//Set uniform
	glUniform1i(shader->texture2DUniform, 0);
	glUniform1i(shader->texture2DUniform2, 1);
	glUniform1i(shader->texture2DUniform3, 2);
	glUniform1i(shader->texture2DUniform4, 3);
	glUniformMatrix4fv(shader->wvpUniform, 1, GL_FALSE, (const GLfloat*)wvpMatrix.m);

	if(shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) VERTEX_OFFSET_POS);
	}
	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) VERTEX_OFFSET_UV);
	}

	glDrawElements(GL_TRIANGLES, model->m_IndexBuffer->m_Count, GL_UNSIGNED_INT, 0);

	model->Unbind();
	for (unsigned int i = 0; i < object->m_iTexture2DID.size(); i++) {
		ResourceManager::GetInstance()->m_Texture2DList[object->m_iTexture2DID[i]]->Unbind();
	}
	shader->Unbind();
}

void Renderer::DrawTerrain(Terrain *terrain, Camera *camera) {
	Model *model = ResourceManager::GetInstance()->m_ModelList[terrain->m_iModelID];
	Shaders *shader = ResourceManager::GetInstance()->m_ShaderList[terrain->m_iShaderID];

	shader->Bind();
	model->Bind();
	for (unsigned int i = 0; i < terrain->m_iTexture2DID.size(); i++) {
		ResourceManager::GetInstance()->m_Texture2DList[terrain->m_iTexture2DID[i]]->Bind(i);
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

	glDrawElements(GL_TRIANGLES, model->m_IndexBuffer->m_Count, GL_UNSIGNED_INT, 0);

	model->Unbind();
	for (unsigned int i = 0; i < terrain->m_iTexture2DID.size(); i++) {
		ResourceManager::GetInstance()->m_Texture2DList[terrain->m_iTexture2DID[i]]->Unbind();
	}
	shader->Unbind();
}
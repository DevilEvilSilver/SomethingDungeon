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

void Renderer::DrawAnimated(Object *object, Camera *camera) {
	Prefab *prefab = GetResource(object->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	Model *model = GetResource(prefab->m_iModelID, ResourceManager::GetInstance()->m_ModelList);
	Shaders *shader = GetResource(prefab->m_iShaderID, ResourceManager::GetInstance()->m_ShaderList);
	Animation *animation = GetResource(object->m_strState, prefab->m_AnimationList);

	shader->Bind();
	model->Bind();
	if (object->m_fCurrFrameTime >= animation->m_FrameList[object->m_iCurrFrameIndex]->m_fSPF) {
		object->m_iCurrFrameIndex = (object->m_iCurrFrameIndex + 1) % animation->m_FrameList.size();
		object->m_fCurrFrameTime = 0.0f;
	}
	animation->m_FrameList[object->m_iCurrFrameIndex]->Bind();

	GLfloat scaleBySize[2][2];
	scaleBySize[0][0] = 1.0f; scaleBySize[0][1] = 0.0f;
	scaleBySize[1][0] = 0.0f; scaleBySize[1][1] = 1.0f;
	Matrix wvpMatrix = object->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	//Set uniform
	glUniform1i(shader->texture2DUniform, 0);
	if (prefab->m_isScaleBySize) {
		scaleBySize[0][0] = prefab->m_fScaleX;
		scaleBySize[1][1] = prefab->m_fScaleY;
	}
	glUniformMatrix2fv(shader->spriteScaleUniform, 1, GL_FALSE, (const GLfloat*)scaleBySize);
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
	animation->m_FrameList[object->m_iCurrFrameIndex]->Unbind();
	shader->Unbind();
}
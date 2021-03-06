#include "stdafx.h"
#include <GLES2/gl2.h>
#include "Renderer.h"
#include "Fader.h"
#include "define.h"
#include "ResourceManager.h"


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



void Renderer::Init() {
	
}

void Renderer::DrawAnimated(Object *object, Camera *camera, Vector2 playerWidgetPos) {
	Prefab *prefab = GetResource(object->m_strPrefabID, ResourceManager::GetInstance()->m_PrefabList);
	Model *model = GetResource(prefab->m_iModelID, ResourceManager::GetInstance()->m_ModelList);
	Shaders *shader = GetResource(prefab->m_iShaderID, ResourceManager::GetInstance()->m_ShaderList);
	Animation *animation = GetResource(object->m_strState, prefab->m_AnimationList);
	
	shader->Bind();
	model->Bind();
	if (animation->m_FrameList[object->m_iCurrFrameIndex]->m_fSPF == -1.0f) {
		object->m_fCurrFrameTime = 0.0f;
	}
	else if (object->m_fCurrFrameTime >= animation->m_FrameList[object->m_iCurrFrameIndex]->m_fSPF) {
		object->m_iCurrFrameIndex = (object->m_iCurrFrameIndex + 1) % animation->m_FrameList.size();
		object->m_fCurrFrameTime = 0.0f;
	}
	animation->m_FrameList[object->m_iCurrFrameIndex]->Bind();
	
	//Set uniform
	glUniform1i(shader->textureUniform, 0);

	GLfloat scaleBySize[2][2];
	scaleBySize[0][0] = 1.0f; scaleBySize[0][1] = 0.0f;
	scaleBySize[1][0] = 0.0f; scaleBySize[1][1] = 1.0f;

	if (object->m_isFacingLeft==false) scaleBySize[0][0] = -1.0f;
	if (object->m_isFacingUp == false) scaleBySize[1][1] = -1.0f;

	if (prefab->m_isScaleBySize) {
		scaleBySize[0][0] = prefab->m_fScaleX;
		scaleBySize[1][1] = prefab->m_fScaleY;
	}
	glUniformMatrix2fv(shader->spriteScaleUniform, 1, GL_FALSE, (const GLfloat*)scaleBySize);

	if (auto* widget = dynamic_cast<Widget*>(object)) {
		Matrix wvpMatrix = widget->GetWorldMatrix(camera) * camera->GetViewMatrix() * camera->GetProjectionMatrix();
		glUniformMatrix4fv(shader->wvpUniform, 1, GL_FALSE, (const GLfloat*)wvpMatrix.m);
		if ((playerWidgetPos.x && playerWidgetPos.y))
		{
			Vector4 pos = { playerWidgetPos.x,playerWidgetPos.y,0,1 };
			pos = pos * camera->GetViewMatrix() * camera->GetProjectionMatrix();
			glUniform1f(shader->playerPosXUniform, pos.x);
			glUniform1f(shader->playerPosYUniform, pos.y);
		}
	} 
	else {
		Matrix wvpMatrix = object->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();
		glUniformMatrix4fv(shader->wvpUniform, 1, GL_FALSE, (const GLfloat*)wvpMatrix.m);
	}

	if (auto* fader = dynamic_cast<Fader*>(object)) {
		glUniform1f(shader->timeUniform, fader->m_fCurrTime);
		glUniform1f(shader->fadeUniform, fader->m_fFadeTime);
	}

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


void Renderer::DrawText2(Text* text) {
	Shaders* shader = GetResource(text->getShaderId(), ResourceManager::GetInstance()->m_ShaderList);
	Font* font = GetResource(text->getFontId(), ResourceManager::GetInstance()->m_FontList);
	GLuint iTempShaderVaribleGLID = -1;

	shader->Bind();

	glBindBuffer(GL_ARRAY_BUFFER, font->getArrBuffer());
	glActiveTexture(GL_TEXTURE0);

	iTempShaderVaribleGLID = shader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}


	iTempShaderVaribleGLID = shader->GetUniformLocation((char*)"u_color");
	if (iTempShaderVaribleGLID != -1)
		glUniform4fv(iTempShaderVaribleGLID, 1, &text->m_Color.x);

	iTempShaderVaribleGLID = shader->GetUniformLocation((char*)"u_texture");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1i(iTempShaderVaribleGLID, 0);
	}

	float sx = 1.0f / SCREEN_W * text->getScale().x;
	float sy = 1.0f / SCREEN_H * text->getScale().y;
	float x = text->m_Vec3Position.x;
	float y = text->m_Vec3Position.y;

	for (const char* p = text->m_text.c_str(); *p; p++)
	{
		Glyph glyph = font->m_Glyphs[*p];

		float x2 = x + glyph.Bearing.x * sx;
		float y2 = -y - glyph.Bearing.y * sy;
		float w = glyph.Size.x * sx;
		float h = glyph.Size.y * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glBindTexture(GL_TEXTURE_2D, glyph.TextureID);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (glyph.AdvanceX >> 6) * sx;
		y += (glyph.AdvanceY >> 6) * sy;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	shader->Unbind();
}
/*
void Renderer::DrawText(Text* text) {
	DrawText2(text);

	/*Text* text2 =  new Text("", 1, 1, TEXT_COLOR::RED, 20, 20, 1.0f);
	text2->setText(text->m_text2);
	text2->Set2DPosition(text->m_Vec2DPos.x, text->m_Vec2DPos.y +20);
	DrawText2(text2);
}*/
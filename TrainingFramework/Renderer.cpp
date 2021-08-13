#include "stdafx.h"
#include <GLES2/gl2.h>
#include "Renderer.h"
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

void Renderer::DrawAnimated(Object *object, Camera *camera) {
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

	GLfloat scaleBySize[2][2];
	scaleBySize[0][0] = 1.0f; scaleBySize[0][1] = 0.0f;
	scaleBySize[1][0] = 0.0f; scaleBySize[1][1] = 1.0f;

	if (object->m_isFacingLeft==false) scaleBySize[0][0] = -1.0f;

	Matrix wvpMatrix = object->GetWorldMatrix() * camera->GetViewMatrix() * camera->GetProjectionMatrix();

	
	//Set uniform
	glUniform1i(shader->textureUniform, 0);
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



void Renderer::DrawText2(Text* text) {
	Shaders* shader = GetResource(text->getShaderId(), ResourceManager::GetInstance()->m_ShaderList);
	Font* font = GetResource(text->getFontId(), ResourceManager::GetInstance()->m_FontList);
	GLuint iTempShaderVaribleGLID = -1;

	shader->Bind();

	glBindBuffer(GL_ARRAY_BUFFER, font->getArrBuffer());


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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, font->getTextFontAdd());
		glUniform1i(iTempShaderVaribleGLID, 0);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float sx = 1.0f / SCREEN_W * text->getScale().x;
	float sy = 1.0f / SCREEN_H * text->getScale().y;
	float x = text->m_Vec3Position.x;
	float y = text->m_Vec3Position.y;

	FT_GlyphSlot glyphSlot = font->getFtGlyph();
	for (const char* p = text->m_text.c_str(); *p; p++)
	{
		if (FT_Load_Char(font->getFtFace(), *p, FT_LOAD_RENDER))
		{
			continue;
		}
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			glyphSlot->bitmap.width,
			glyphSlot->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			glyphSlot->bitmap.buffer
		);
		float x2 = x + glyphSlot->bitmap_left * sx;
		float y2 = -y - glyphSlot->bitmap_top * sy;
		float w = glyphSlot->bitmap.width * sx;
		float h = glyphSlot->bitmap.rows * sy;
		GLfloat box[4][4] = {
			{x2, -y2 , 0, 0},
			{x2 + w, -y2 , 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		x += (glyphSlot->advance.x >> 6) * sx;
		y += (glyphSlot->advance.y >> 6) * sy;
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
#pragma once
#include "../Utilities/utilities.h"
#include "Camera.h"

class Shaders 
{
public:
	unsigned int m_iResourceID;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	bool m_isDepthTest, m_isCulling, m_isBlend;
	GLint positionAttribute;
	GLint uvAttribute;
	GLint texture2DUniform, texture2DUniform2, texture2DUniform3, texture2DUniform4;
	GLint spriteScaleUniform;
	GLint wvpUniform;

	Shaders(unsigned int resourceID, char * fileVertexShader, char * fileFragmentShader, bool isDepthTest, bool isCulling, bool isBlend);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();

	void Bind();
	void Unbind();
};
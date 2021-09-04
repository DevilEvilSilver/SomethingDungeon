#pragma once
#include <string>
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
	GLint textureUniform;
	GLint spriteScaleUniform;
	GLint timeUniform;
	GLint fadeUniform;
	GLint wvpUniform;
	GLint playerPosXUniform;
	GLint playerPosYUniform;

	Shaders(unsigned int resourceID, char * fileVertexShader, char * fileFragmentShader, bool isDepthTest, bool isCulling, bool isBlend);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();

	void Bind();
	void Unbind();

	//Tien add
	Shaders() {}
	GLuint GetAttribLocation(const std::string& str);
	GLuint GetUniformLocation(const std::string& str);
};
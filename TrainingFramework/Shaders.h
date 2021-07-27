#pragma once
#include "../Utilities/utilities.h"
#include "Camera.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	bool m_isDepthTest, m_isCulling, m_isBlend;
	GLint positionAttribute;
	GLint uvAttribute;
	GLint texture2DUniform, texture2DUniform2, texture2DUniform3, texture2DUniform4;
	GLint heightmapUniform;
	GLint fogStartUniform, fogLengthUniform, fogColorUniform;
	GLint cameraPosUniform;
	GLint textureCubeUniform;
	GLint TimeUniform;
	GLint wvpUniform;

	Shaders(char * fileVertexShader, char * fileFragmentShader, bool isDepthTest, bool isCulling, bool isBlend);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();

	void Bind();
	void Unbind();
};
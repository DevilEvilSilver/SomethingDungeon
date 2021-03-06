#include "stdafx.h"
#include "Shaders.h"


Shaders::Shaders(unsigned int resourceID, char * fileVertexShader, char * fileFragmentShader, bool isDepthTest, bool isCulling, bool isBlend)
	: m_iResourceID(resourceID), m_isDepthTest(isDepthTest), m_isCulling(isCulling), m_isBlend(isBlend) {
	this->Init(fileVertexShader, fileFragmentShader);
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	textureUniform = glGetUniformLocation(program, "u_texture");
	spriteScaleUniform = glGetUniformLocation(program, "u_spriteScale");
	timeUniform = glGetUniformLocation(program, "u_time");
	fadeUniform = glGetUniformLocation(program, "u_fade");
	wvpUniform = glGetUniformLocation(program, "u_wvp");
	playerPosXUniform = glGetUniformLocation(program, "u_playerPosX");
	playerPosYUniform = glGetUniformLocation(program, "u_playerPosY");




	

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shaders::Bind() {
	if (m_isDepthTest) {
		glEnable(GL_DEPTH_TEST);
	}
	if (m_isCulling) {
		glEnable(GL_CULL_FACE);
	}
	if (m_isBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glUseProgram(program);
}

void Shaders::Unbind() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glUseProgram(0);
}

// Tien add
GLuint Shaders::GetAttribLocation(const std::string& str)
{
	return glGetAttribLocation(program, str.c_str());
}

GLuint Shaders::GetUniformLocation(const std::string& str)
{
	return glGetUniformLocation(program, str.c_str());
}
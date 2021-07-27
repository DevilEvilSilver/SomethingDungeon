#include <stdafx.h>
#include "Shaders.h"

Shaders::Shaders(char * fileVertexShader, char * fileFragmentShader, bool isDepthTest, bool isCulling, bool isBlend)
	: m_isDepthTest(isDepthTest), m_isCulling(isCulling), m_isBlend(isBlend) {
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
	texture2DUniform = glGetUniformLocation(program, "u_texture");
	texture2DUniform2 = glGetUniformLocation(program, "u_texture1");
	texture2DUniform3 = glGetUniformLocation(program, "u_texture2");
	texture2DUniform4 = glGetUniformLocation(program, "u_texture3");
	heightmapUniform = glGetUniformLocation(program, "u_heightmap");
	fogStartUniform = glGetUniformLocation(program, "u_fogStart");
	fogLengthUniform = glGetUniformLocation(program, "u_fogLength");
	fogColorUniform = glGetUniformLocation(program, "u_fogColor");
	cameraPosUniform = glGetUniformLocation(program, "u_cameraPos");
	textureCubeUniform = glGetUniformLocation(program, "u_cubeMap");
	TimeUniform = glGetUniformLocation(program, "u_time");
	wvpUniform = glGetUniformLocation(program, "u_wvp");

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
#include "stdafx.h"
#include <string>
#include "ResourceManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

Model* LoadModel(char* file);

ResourceManager * ResourceManager::s_Instance = NULL;

ResourceManager::ResourceManager(void) {
	this->Init();
}

ResourceManager::~ResourceManager() {
	for (auto& object : m_ModelList) {
		delete object;
	}
	m_ModelList.resize(0);
	for (auto& object : m_Texture2DList) {
		delete object;
	}
	m_Texture2DList.resize(0);
	for (auto& object : m_ShaderList) {
		delete object;
	}
	m_ShaderList.resize(0);
}

ResourceManager* ResourceManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new ResourceManager();
	return s_Instance;
}

void ResourceManager::ResetInstance() {
	delete s_Instance;
	s_Instance = NULL;
}

void ResourceManager::Init() {
	FILE* dataFile;
	dataFile = fopen(FILE_RM, "r");

	int iModelCount;
	fscanf(dataFile, "#MODEL_COUNT %d\n", &iModelCount);
	while (iModelCount--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		char strNFGFile[100];
		fscanf(dataFile, "FILE %s\n", &strNFGFile);
		AddModel(LoadModel(strNFGFile));
	}

	int i2DTextureCount;
	fscanf(dataFile, "#2D_TEXTURE_COUNT %d\n", &i2DTextureCount);
	while (i2DTextureCount--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		char strTGAFile[100];
		fscanf(dataFile, "FILE %s\n", &strTGAFile);
		char strTiling[30];
		GLint iTiling = 0;
		fscanf(dataFile, "TILING %s\n", &strTiling);
		if (!strcmp(strTiling, "GL_REPEAT"))
			iTiling = GL_REPEAT;
		else if (!strcmp(strTiling, "GL_CLAMP_TO_EDGE"))
			iTiling = GL_CLAMP_TO_EDGE;
		else if (!strcmp(strTiling, "GL_MIRRORED_REPEAT"))
			iTiling = GL_MIRRORED_REPEAT;

		Texture *texture = new Texture(strTGAFile, iTiling);
		AddTexture2D(texture);
	}

	int iShaderCount;
	fscanf(dataFile, "#SHADER_COUNT %d\n", &iShaderCount);
	while (iShaderCount--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		char strVSFile[100];
		fscanf(dataFile, "VS %s\n", &strVSFile);
		char strFSFile[100];
		fscanf(dataFile, "FS %s\n", &strFSFile);
		int iStateCount;
		fscanf(dataFile, "STATE_COUNT %d\n", &iStateCount);
		unsigned int isDepthTest = 0, isCulling = 0, isBlend = 0;
		if (iStateCount > 0) 
			fscanf(dataFile, "GL_DEPTH_TEST %d\n", &isDepthTest);
		if (iStateCount > 1) 
			fscanf(dataFile, "GL_CULL_FACE %d\n", &isCulling);
		if (iStateCount > 2)
			fscanf(dataFile, "GL_BLEND %d\n", &isBlend);
		Shaders *shader = new Shaders(strVSFile, strFSFile, isDepthTest, isCulling, isBlend);
		AddShader(shader);
	}

	fclose(dataFile);
}

void ResourceManager::AddModel(Model *model) {
	m_ModelList.push_back(model);
}

void ResourceManager::AddTexture2D(Texture *texture) {
	m_Texture2DList.push_back(texture);
}

void ResourceManager::AddShader(Shaders *shader) {
	m_ShaderList.push_back(shader);
}

Model* LoadModel(char* file) {
	GLuint iVerticesCount, iIndicesCount;
	FILE* dataFile = fopen(file, "r");
	fscanf(dataFile, "NrVertices: %d\n", &iVerticesCount);
	GLuint iVerticesLoopCount = iVerticesCount;
	Vertex *vertices = new Vertex[iVerticesCount];

	while (iVerticesLoopCount--) {
		GLuint i;
		GLfloat fPosX, fPosY, fPosZ, fNormX, fNormY, fNormZ, fBinormX, fBinormY, fBinormZ, fTgtX, fTgtY, fTgtZ, fUvX, fUvY;
		fscanf(dataFile,
			"%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&i, &fPosX, &fPosY, &fPosZ, &fNormX, &fNormY, &fNormZ, &fBinormX, &fBinormY, &fBinormZ, &fTgtX, &fTgtY, &fTgtZ, &fUvX, &fUvY);

		vertices[i].pos.x = fPosX; vertices[i].pos.y = fPosY; vertices[i].pos.z = fPosZ;
		vertices[i].norm.x = fNormX; vertices[i].norm.y = fNormY; vertices[i].norm.z = fNormZ;
		vertices[i].binorm.x = fBinormX; vertices[i].binorm.y = fBinormY; vertices[i].binorm.z = fBinormZ;
		vertices[i].tgt.x = fTgtX; vertices[i].tgt.y = fTgtY; vertices[i].tgt.z = fTgtZ;
		vertices[i].uv.x = fUvX; vertices[i].uv.y = fUvY;
	}

	fscanf(dataFile, "NrIndices: %d\n", &iIndicesCount);
	GLuint iTrianglesCount = iIndicesCount / 3;
	GLuint *indices = new GLuint[iIndicesCount];

	while (iTrianglesCount--) {
		GLuint i;
		GLuint iVertex1, iVertex2, iVertex3;
		fscanf(dataFile,
			"   %d.    %d,    %d,    %d\n",
			&i, &iVertex1, &iVertex2, &iVertex3);

		indices[i * 3] = iVertex1;
		indices[i * 3 + 1] = iVertex2;
		indices[i * 3 + 2] = iVertex3;
	}

	Model *model = new Model(vertices, sizeof(Vertex) * iVerticesCount, indices, iIndicesCount);
	delete[]vertices;
	delete[]indices;

	return model;
}

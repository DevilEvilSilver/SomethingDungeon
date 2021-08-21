#include "stdafx.h"
#include <string>
#include "ResourceManager.h"
#include "define.h"
#define _CRT_SECURE_NO_WARNINGS

Model* LoadModel(unsigned int id, char* file);
Model* GenModel(unsigned int id, float width, float height);



ResourceManager::ResourceManager(void) {

}

ResourceManager::~ResourceManager() {
	for (auto& object : m_ModelList) {
		delete object;
	}
	for (auto& object : m_PrefabList) {
		delete object;
	}
	m_PrefabList.resize(0);
	for (auto& object : m_ShaderList) {
		delete object;
	}
	m_ShaderList.resize(0);
	for (auto& object : m_FontList) {
		delete object;
	}
	m_FontList.resize(0);
}



void ResourceManager::Init(std::string resourceFile) {
	FILE* dataFile;
	dataFile = fopen(resourceFile.c_str(), "r");

	int iPrefabCount;
	fscanf(dataFile, "#PREFAB_COUNT %d\n", &iPrefabCount);
	while (iPrefabCount--) {
		char strPrefabID[50];
		fscanf(dataFile, "ID %s\n", &strPrefabID);

		unsigned int iModel;
		fscanf(dataFile, "MODEL %d\n", &iModel);

		unsigned int iShader;
		fscanf(dataFile, "SHADER %d\n", &iShader);
		
		char strType[50];
		unsigned int iType;
		GLfloat fPosX, fPosY, fWidth = 0.0f, fHeight = 0.0f, fRadius = 0.0f;
		fscanf(dataFile, "TYPE %s\n", &strType);
		if (!strcmp(strType, "RECT")) {
			iType = RECTANGLE;
			fscanf(dataFile, "COORD %f, %f, %f, %f\n", &fPosX, &fPosY, &fWidth, &fHeight);
		}
		else if (!strcmp(strType, "CIRCLE")) {
			iType = CIRCLE;
			fscanf(dataFile, "COORD %f, %f, %f\n", &fPosX, &fPosY, &fRadius);
		}
		
		GLfloat fScaleX, fScaleY;
		fscanf(dataFile, "SIZE %f x %f\n", &fScaleX, &fScaleY);

		unsigned int isScaleBySize;
		fscanf(dataFile, "SCALE_BY_SIZE %d\n", &isScaleBySize);

		Prefab *prefab = new Prefab(strPrefabID, iModel, iShader, iType, fPosX, fPosY, fWidth, fHeight, fRadius, fScaleX, fScaleY, isScaleBySize);
		
		int iAnimationCount;
		fscanf(dataFile, "ANIMATION_COUNT %d\n", &iAnimationCount);
		while (iAnimationCount--) {
			char strAnimId[50];
			fscanf(dataFile, "ID %s\n", &strAnimId);
			char strAnimationFile[100];
			fscanf(dataFile, "FILE %s\n", &strAnimationFile);
	
			Animation *animation = new Animation(strAnimId, strAnimationFile);
			prefab->AddAnamation(animation);
		}
		
		AddPrefab(prefab);
	}

	int iModelGen;
	fscanf(dataFile, "#MODEL_GEN %d\n", &iModelGen);
	while (iModelGen--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		float width, height;
		fscanf(dataFile, "SIZE %f x %f\n", &width, &height);
		AddModel(GenModel(id, width, height));
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
		Shaders *shader = new Shaders(id, strVSFile, strFSFile, isDepthTest, isCulling, isBlend);
		AddShader(shader);
	}
	
	int fontCount;
	fscanf(dataFile, "#FONT_COUNT %d\n", &fontCount);
	while (fontCount--) {
		int id;
		fscanf(dataFile, "ID %d\n", &id);
		char fontFile[100];
		fscanf(dataFile, "FILE %s\n", &fontFile);
		Font* font = new Font(id, fontFile);
		AddFont(font);
	}

	fclose(dataFile);
}

void ResourceManager::AddModel(Model *model) {
	m_ModelList.push_back(model);
}

void ResourceManager::AddPrefab(Prefab *prefab) {
	m_PrefabList.push_back(prefab);
}

void ResourceManager::AddShader(Shaders *shader) {
	m_ShaderList.push_back(shader);
}

void ResourceManager::AddFont(Font* font) {
	m_FontList.push_back(font);
}

Model* LoadModel(unsigned int id, char* file) {
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

	Model *model = new Model(id, vertices, sizeof(Vertex) * iVerticesCount, indices, iIndicesCount);
	delete[]vertices;
	delete[]indices;

	return model;
}

Model* GenModel(unsigned int id, float width, float height) {
	Vertex *vertices = new Vertex[4];

	vertices[0].pos.x = 0.0f; vertices[0].pos.y = -height; vertices[0].pos.z = 0.0f;
	vertices[0].uv.x = 0.0f; vertices[0].uv.y = 0.0f;
	vertices[1].pos.x = 0.0f; vertices[1].pos.y = 0.0f; vertices[1].pos.z = 0.0f;
	vertices[1].uv.x = 0.0f; vertices[1].uv.y = 1.0f;
	vertices[2].pos.x = width; vertices[2].pos.y = 0.0f; vertices[2].pos.z = 0.0f;
	vertices[2].uv.x = 1.0f; vertices[2].uv.y = 1.0f;
	vertices[3].pos.x = width; vertices[3].pos.y = -height; vertices[3].pos.z = 0.0f;
	vertices[3].uv.x = 1.0f; vertices[3].uv.y = 0.0f;
	
	GLuint *indices = new GLuint[6];

	indices[0] = 0; indices[1] = 2; indices[2] = 1;
	indices[3] = 0; indices[4] = 3; indices[5] = 2;

	Model *model = new Model(id, vertices, sizeof(Vertex) * 4, indices, 6);
	delete[]vertices;
	delete[]indices;

	return model;
}


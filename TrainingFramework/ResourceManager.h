#pragma once
#include <vector>
#include "Vertex.h"
#include "Model.h"
#include "Texture2D.h"
#include "Shaders.h"

class ResourceManager {
private:
	static ResourceManager* s_Instance;

public:
	std::vector<Model*> m_ModelList;
	std::vector<Texture2D*> m_Texture2DList;
	std::vector<Shaders*> m_ShaderList;

	ResourceManager();
	~ResourceManager();

	void Init();

	void AddModel(Model *model);
	void AddTexture2D(Texture2D *texture);
	void AddShader(Shaders *shader);

	static ResourceManager* GetInstance();
	static void ResetInstance();
};
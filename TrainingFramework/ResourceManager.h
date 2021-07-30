#pragma once
#include <vector>
#include "Vertex.h"
#include "Model.h"
#include "Animation.h"
#include "Prefab.h"
#include "Shaders.h"

class ResourceManager {
private:
	static ResourceManager* s_Instance;

public:
	std::vector<Model*> m_ModelList;
	std::vector<Prefab*> m_PrefabList;
	std::vector<Shaders*> m_ShaderList;

	ResourceManager();
	~ResourceManager();

	void Init();

	void AddModel(Model *model);
	void AddPrefab(Prefab *prefab);
	void AddShader(Shaders *shader);

	static ResourceManager* GetInstance();
	static void ResetInstance();
};
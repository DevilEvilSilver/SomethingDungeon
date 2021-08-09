#pragma once
#include <vector>
#include "Vertex.h"
#include "Model.h"
#include "Animation.h"
#include "Prefab.h"
#include "Shaders.h"
#include "Font.h"

#include "Singleton.h"

class ResourceManager:public Singleton<ResourceManager> {

public:
	std::vector<Model*> m_ModelList;
	std::vector<Prefab*> m_PrefabList;
	std::vector<Shaders*> m_ShaderList;
	std::vector<Font*> m_FontList;

	ResourceManager();
	~ResourceManager();

	void Init();

	void AddModel(Model *model);
	void AddPrefab(Prefab *prefab);
	void AddShader(Shaders *shader);
	void AddFont(Font* font);

};
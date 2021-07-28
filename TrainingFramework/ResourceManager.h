#pragma once
#include <vector>
#include "Vertex.h"
#include "Model.h"
#include "Animation.h"
#include "Shaders.h"

class ResourceManager {
private:
	static ResourceManager* s_Instance;

public:
	std::vector<Model*> m_ModelList;
	std::vector<Texture*> m_Texture2DList;
	std::vector<Animation*> m_AnimationList;
	std::vector<Shaders*> m_ShaderList;

	ResourceManager();
	~ResourceManager();

	void Init();

	void AddModel(Model *model);
	void AddTexture2D(Texture *texture);
	void AddAnamation(Animation *animation);
	void AddShader(Shaders *shader);

	static ResourceManager* GetInstance();
	static void ResetInstance();
};
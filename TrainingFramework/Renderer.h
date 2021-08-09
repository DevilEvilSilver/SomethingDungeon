#pragma once
#include <vector>
#include "Object.h"
#include "Singleton.h"

class Renderer:public Singleton<Renderer> {


public:
	Renderer();
	~Renderer();

	void Init();
	void DrawAnimated(Object *object, Camera *camera);


};
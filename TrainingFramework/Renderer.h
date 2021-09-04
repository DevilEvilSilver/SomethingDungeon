#pragma once
#include <vector>
#include "Object.h"
#include "Text.h"
#include "Singleton.h"

class Renderer:public Singleton<Renderer> {


public:
	Renderer();
	~Renderer();

	void Init();
	void DrawAnimated(Object* object, Camera* camera, Vector2 playerWidgetPos = {0,0});
	void DrawText2(Text* text);
	//void DrawText(Text* text);


};
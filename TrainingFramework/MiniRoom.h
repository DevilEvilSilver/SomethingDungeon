#pragma once
#include "Widget.h"
class MiniRoom :
    public Widget
{
public:
	MiniRoom(std::string prefabID, Vector2 roomID, Matrix translationMatrix,Vector2 size);
	virtual ~MiniRoom();

	/*virtual void Update(float frameTime);
	virtual void Render(Camera* camera);

	Matrix GetWorldMatrix(Camera* camera);*/

	void ReSize(Vector2 size);
};



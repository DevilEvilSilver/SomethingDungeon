#pragma once
#include "Character.h"
#include"Gold.h"

class Enemy : public Character {
private:
	Gold* m_gold;
	int m_inumGold;	
	Matrix m_translationMatrix;
	
public:
	bool isDead ;

	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();

	void Update(float frameTime);
	void Render(Camera *camera);

	void setGold(Gold* gold) { m_gold = gold; }
	Gold* getGold() {return m_gold;}
	Matrix getTranslationMatrix() { return m_translationMatrix; }
	void createGoldObject();
};
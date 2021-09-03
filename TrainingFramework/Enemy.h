#pragma once
#include "Character.h"
#include"Gold.h"
#include "EnemyHpMob.h"

class Enemy : public Character {
protected:
	EnemyHpMob *m_HpMob;
	float m_fcurrCDTimeHpMob;
	float m_CDTimeHpmob;
	float m_fLastCurrHp;
public:

	/////////////////////////////////////////////////
	
	//AI
	virtual void UniqueUpdate(float frameTime);

	//DROP
	bool isDead ;

	//ATTACK DELAY
	float delayTime = 0.1f;

	//Death Time
	float deathTime = 1.0f;

	//OPTION
	void Chase(Vector2 delta);
	void KeepDistance(Vector2 delta);

	bool start = false;
	Vector2 ranDir = Vector2(0.0f, 0.0f);
	bool MoveRandom(float frameTime);


	//SKILL
	virtual void UseSkill(float frameTime);
	
	virtual void Death(float frameiIme);
	

	//OTHER
	Enemy();
	Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix);
	~Enemy();


	virtual void Render(Camera* camera);

	void UpdateHpMob(float frameTime);
	virtual void createDrop();
};
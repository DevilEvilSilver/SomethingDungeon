#include "stdafx.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "define.h"
#include "StatePlay.h"
#include "CollisionManager.h"

#include "BulletSkill.h"
#include "AoeSkill.h"

#include "SoundEngine.h"
Enemy::Enemy() {}
Enemy::Enemy(std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	: Character(prefabID, roomID, translationMatrix) {

	m_fcurrCDTimeHpMob = 0;
	m_CDTimeHpmob = 3;
	m_maxHP = 10;
	m_currHP = 10;

	m_ATK = 3;
	m_DEF = 3;

	m_strState = IDLE_LEFT;
	isWallCollision = true; 
	isPlayerCollision = false;
	isEnemyCollision = true;

	m_MOVESPEED = 3.0f;
	isDead = false;
	m_fLastCurrHp = m_maxHP;
	
	m_HpMob = new EnemyHpMob(roomID, translationMatrix, m_maxHP, m_currHP);
	
}
Enemy::~Enemy() {
	delete m_HpMob;
}
void Enemy::UniqueUpdate(float frameTime)
{
	Player* plyr = StatePlay::GetInstance()->m_Player;
	Vector2 plyPos = plyr->GetPos();
	Vector2 enmyPos = GetPos();

	Vector2 delta = plyPos - enmyPos;
	float distance = delta.Length();
	
	//move behavior
	m_MOVESPEED = 3.0f;
	if (distance < 4.0f /*&& distance > 5.0f*/)
	{
		KeepDistance(delta);
		m_MOVESPEED = 4.0f;
	}
		
	else if (distance < 6.0f)
	{
		
		UseSkill(frameTime);
		MoveRandom(frameTime);

		//	//currCD -= frameTime;
		//}
	}

	

}
void Enemy::UpdateHpMob(float frameTime)
{
	m_fcurrCDTimeHpMob -= frameTime;
	m_HpMob->Update(frameTime);
	m_HpMob->SetWorldPos(Vector2(m_fCurrentPosX -m_fDeltaX/2, m_fCurrentPosY + m_fDeltaY));
	if (m_fLastCurrHp - m_currHP)
		m_fcurrCDTimeHpMob = m_CDTimeHpmob;
	if (isDead == true)
	{
		m_HpMob->Resize(0);
	}
	else
		m_HpMob->Resize(m_currHP);
	m_fLastCurrHp = m_currHP;
}
//ACTION
void Enemy::Chase(Vector2 delta)
{
	if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
	UpdateMoveDirection(delta);
}
void Enemy::KeepDistance(Vector2 delta)
{
	if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
	UpdateMoveDirection(-delta);
}

bool Enemy::MoveRandom(float frameTime)
{
	

	if (start == false)
	{
		
		ranDir = Vector2(rand()%10, rand()%10);
		if (rand() % 2 == 0) ranDir.x *= -1;
		if (rand() % 2 == 0) ranDir.y *= -1;
		start = true;

		//if (m_cState != CS_MOVE && m_cState != CS_GOTHIT && m_cState != CS_DEATH) SetCS(CS_MOVE);
		ResetAnimation();
		
	
	}
	if (start == true)
	{
		m_strState = MOVE;
		if (FixedMove(ranDir, m_MOVESPEED*0.5f, 0.5f, frameTime) == false) return false;
		start = false;
		ResetAnimation();
		return true;
			
		
	}
	return false;
}

//SKILL
//----------------------------------------

//----------------------------------------

void Enemy::Death(float frameTime)
{
	m_strState = DEATH;
	
	if (FixedMove(Vector2(0,0),0.0f,2.0f, frameTime) == true) {
		SoundEngine::GetInstance()->Play(COIN, 1.0f, 1.0f, false);
		isDead = true;
		createDrop();
	}
}

//OTHER

void Enemy::Render(Camera* camera)
{

	Renderer::GetInstance()->DrawAnimated(this, camera);
	if(m_fcurrCDTimeHpMob > 0)
		m_HpMob->Render(camera);
}


void Enemy::createDrop()
{
	unsigned int random = rand() % 100 + 1;

	Matrix translation;
	translation.SetTranslation(GetCenterPos().x, GetCenterPos().y, 0.0f);

	
	if (random >= 75)
	{
		HPPotion* hp = new HPPotion(HP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(hp);
	}
	else if (random >= 50)
	{
		MPPotion* mp = new MPPotion(MP_PO, m_RoomID, translation);
		StatePlay::GetInstance()->AddDrop(mp);
	}
	else
	{
		Gold* gold = new Gold(GOLD, m_RoomID, translation, 5, false);
		StatePlay::GetInstance()->AddDrop(gold);
	}
		
}
void Enemy::UseSkill(float frameTime)
{
	
	
}
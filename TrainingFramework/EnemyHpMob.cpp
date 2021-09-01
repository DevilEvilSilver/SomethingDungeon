#include "stdafx.h"
#include "EnemyHpMob.h"
#include "define.h"
EnemyHpMob::EnemyHpMob(Vector2 roomID, Matrix translationMatrix, float maxValue, float currValue,float barSize)
{
	m_Bound = new BarMob(ENEMY_HPMOB_BOUND, roomID, translationMatrix, maxValue, maxValue,barSize);
	m_HpMob = new BarMob(ENEMY_HPMOB, roomID, translationMatrix, maxValue, currValue,barSize);
	
}
EnemyHpMob::~EnemyHpMob()
{
	delete m_Bound;
	delete m_HpMob;
}
void EnemyHpMob::Update(float framTime)
{
	m_Bound->Update(framTime);
	m_HpMob->Update(framTime);
}
void EnemyHpMob::Render(Camera* camera)
{
	m_HpMob->Render(camera);
	m_Bound->Render(camera);
}
void EnemyHpMob::Resize(float value)
{
	m_HpMob->Resize(value);
}
void EnemyHpMob::SetWorldPos(Vector2 pos)
{
	m_Bound->SetWorldPos(pos);
	m_HpMob->SetWorldPos(pos);
}

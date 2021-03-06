#include "stdafx.h"
#include "BulletSkill.h"
#include "StatePlay.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Room.h"
#include "define.h"
#include "AoeSkill.h"
//#include "Effect.h"
BulletSkill::BulletSkill( Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{
	m_SkillDamage = SkillDamage::BULLET_DAMAGE;
	m_ExsitingTime = SkillExistingTime::BULLET_EXISTINGTIME;
	Init(prefabID,Vector2(0,0));
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;
	m_isKnockBack = true;
	m_isFacingUp = false;
	m_isFacingLeft = true;
}
BulletSkill::BulletSkill(Vector2 target, Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Skill(owner, prefabID, roomID, translationMatrix)
{

	m_SkillDamage = SkillDamage::BULLET_DAMAGE;
	m_ExsitingTime = SkillExistingTime::BULLET_EXISTINGTIME;
	m_damage = owner->m_ATK * (float)m_SkillDamage / 100;
	m_isKnockBack = true;
	Init(prefabID,target);
}
BulletSkill::~BulletSkill()
{
}

void BulletSkill::UpdateHit(float frameTime)
{
	if (m_bHit)
	{
		Vector2 curPos = Vector2(m_fCurrentPosX + m_fDeltaX, m_fCurrentPosY - m_fDeltaY);
		if (m_isPlayer)
		{

			for (auto& enemy : StatePlay::GetInstance()->m_InRangeEnemy)
			{

				if (CollisionManager::CheckCollision(this, enemy))
				{
					//enemy->isAttacked
					m_bHit = false;
					isFinished = true;
					Matrix t; t.SetIdentity();
					Effect* effect = new Effect(Vector2(0, 0), EffectExistingTime::EFFECT_SKILL_EXISTINGTIME, this->m_EffectID, enemy->m_RoomID, t, enemy);
					StatePlay::GetInstance()->AddEffect(effect);
					enemy->UpdateGotHit(m_damage, m_isKnockBack, GetCenterPos(), frameTime);
				}

			}
		}
		else
		{

			if (CollisionManager::CheckCollision(this, StatePlay::GetInstance()->m_Player))
			{
				StatePlay::GetInstance()->m_Player->UpdateGotHit(m_damage, m_isKnockBack, curPos, frameTime);
				//StatePlay::GetInstance()->m_Player->numHPText->setText("HP: " + std::to_string(StatePlay::GetInstance()->m_Player->m_currHP));
				isFinished = true;
				m_bHit = false;
			}
		}
		std::vector<Room*> roomList = StatePlay::GetInstance()->m_InRangeRoom;
		for (auto& obj : roomList) {
			if (obj->m_RoomType == WALL)
			{

				if (CollisionManager::CheckCollision(this, obj))
				{
					isFinished = true;
					m_bHit = false;
				}
			}
		}
	}

	for (auto& obj : StatePlay::GetInstance()->m_InRangeDecoration) {
		{
			if (CollisionManager::CheckCollision(this, obj))
			{
				obj->hp--;
				isFinished = true;
			}
		}
	}

}
void BulletSkill::Init(std::string ID,Vector2 target)
{
	/*if (m_isPlayer)
		target = InputManager::GetInstance()->GetMousePosition(StatePlay::GetInstance()->m_Camera, InputManager::GetInstance()->mouseLX, InputManager::GetInstance()->mouseLY);
	else
	{
		Player* player = StatePlay::GetInstance()->m_Player;
		target.x = player->GetPosX() + player->m_fWidth / 2;
		target.y = player->GetPosY() - player->m_fHeight / 2;
	}*/
	/*if (m_owner->GetPosX() > target.x)
		m_isFacingLeft = true;
	else
		m_isFacingLeft = false;*/
	Vector2 dir = target - m_owner->GetCenterPos();
	if(m_isPlayer)
		DirectionPrefab(ID,dir);
	float fminDis = 0.5f;
	float* ownerData = m_owner->GetHitBoxCurrentData();
	Vector2 c1(ownerData[0] / 2.0f + ownerData[2] / 2.0f, ownerData[1] / 2.0f + ownerData[3] / 2.0f);
	mp_dir = (target - c1).Normalize();
	Vector2 startPos = c1 + mp_dir * fminDis;
	m_fCurrentPosX = startPos.x - m_fWidth / 2.0f;
	m_fCurrentPosY = startPos.y + m_fHeight / 2.0f;
	m_WorldMatrix.m[3][0] = m_fCurrentPosX - m_fDeltaX;
	m_WorldMatrix.m[3][1] = m_fCurrentPosY - m_fDeltaY;
	m_fVx = mp_dir.x * BULLET_SPEED;
	m_fVy = mp_dir.y * BULLET_SPEED;
	delete[] ownerData;

}

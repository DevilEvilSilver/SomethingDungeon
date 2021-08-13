
#include "stdafx.h"
#include "Skill.h"
#include "Camera.h"
#include "Renderer.h"
#include "define.h"
#include "SceneManager.h"

Skill::Skill(Character* owner, std::string prefabID, Vector2 roomID, Matrix translationMatrix)
	:Object(prefabID, roomID, translationMatrix)
{
	if (owner == SceneManager::GetInstance()->m_Player)
		m_isPlayer = true;
	else
		m_isPlayer = false;
	m_strState = IDLE_LEFT;
	m_owner = owner;
	m_currExistingTime = 0;
}
Skill::~Skill()
{
}
void Skill::Update(float frameTime)
{
	
}
void Skill::UpdateMove(float frameTime)
{

}
void Skill::UpdateHit(float frameTime)
{
	//character->isAttacked(m_damage)
}
void Skill::Render(Camera* camera)
{
	Renderer::GetInstance()->DrawAnimated(this, camera);
}
void Skill::UpdateExistingTime(float frameTime)
{
	m_currExistingTime += frameTime;
	if (m_currExistingTime > (float)m_totalExsitingTime / 1000)
	{
		Remove();
	}
}
void Skill::Remove()
{
	std::vector<Skill*> skillList = SceneManager::GetInstance()->m_SkillList;
	for (int i = 0; i<skillList.size(); i++ )
	{
		if (this == skillList[i])
		{
			delete this;
			SceneManager::GetInstance()->m_SkillList.erase(SceneManager::GetInstance()->m_SkillList.begin() + i);
		}
	}
}

#include "stdafx.h"
#include "StateBase.h"
#include "StateManager.h"

StateBase* StateBase::s_Instance = NULL;

StateBase::StateBase()
{
}

StateBase::~StateBase()
{
}

void StateBase::Init()
{

}

void StateBase::Update(float frameTime)
{
	//StateManager::GetInstance()->AddState(StateManager::GetInstance()->GS_STAGE);
}

void StateBase::Render()
{
	//graphic engine
}

void StateBase::AddObjectInstance(ObjectInstance* objectInstance)
{
	m_StateOjectList.push_back(objectInstance);
}

StateBase* StateBase::GetInstance()
{
	if (!s_Instance)
		s_Instance = new StateBase();
	return s_Instance;
}

void StateBase::ResetInstance()
{
	delete s_Instance;
	s_Instance = NULL;
}

#include "stdafx.h"
#include "StateMonsterSearch.h"

#include "Monster.h"
#include "Navigation.h"


CStateMonsterSearch::CStateMonsterSearch()
	:m_pMonster(nullptr)
{
}


CStateMonsterSearch::~CStateMonsterSearch()
{
}

bool CStateMonsterSearch::InitializeState(void* _arg)
{
	CMonster* monster = (CMonster*)_arg;

	if (!monster)
		return false;

	m_pMonster = monster;

	return true;
}

void CStateMonsterSearch::Excute()
{
	CGameObject* player = CObjectManager::GetInstance()->GetLayer(L"LAYER_PLAYER").front();
	vec2	playerPos = dynamic_cast<CTransform*>(player->GetComponent(L"COMPONENT_TRANSFORM"))->GetPosition();

	CTransform*		monsterTransform = dynamic_cast<CTransform*>(m_pMonster->GetComponent(L"COMPONENT_TRANSFORM"));
	CNavigation*	navigation = dynamic_cast<CNavigation*>(m_pMonster->GetComponent(L"COMPONENT_NAVIGATION"));

	vec2	postPos = navigation->SearchingMove(monsterTransform->GetPosition(), playerPos);

	monsterTransform->SetPosition(postPos);

	m_pHander->ChangeState(L"IDLE");
}

bool CStateMonsterSearch::Enter()
{
	return true;
}

bool CStateMonsterSearch::Exit()
{
	return true;
}

CStateMonsterSearch * CStateMonsterSearch::Create(CGameObject* _monster)
{
	CStateMonsterSearch* pInstance = new CStateMonsterSearch;
	if (!pInstance->InitializeState(_monster))
		SAFE_DELETE(pInstance);

	return pInstance;
}

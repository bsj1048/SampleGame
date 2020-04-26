#include "stdafx.h"
#include "Monster.h"

#include "Scene.h"
#include "Navigation.h"
#include "StateHandler.h"

#include "StateMonsterIdle.h"
#include "StateMonsterSearch.h"

CMonster::CMonster()
	:m_pStateHanderCom(nullptr)
	, m_pNavigationCom(nullptr)
{
}


CMonster::~CMonster()
{
}

bool CMonster::InitializeGameObject(void * _arg)
{
	m_tOriginPosition = *(vec2*)_arg;

	AddComponentToMap(L"COMPONENT_TRANSFORM", m_pTransformCom = CTransform::Create(m_tOriginPosition, 1));

	m_pNavigationCom = CCore::GetInstance()->GetCurrentScene()->GetNavigation();
	AddComponentToMap(L"COMPONENT_NAVIGATION", m_pNavigationCom);
	m_pNavigationCom->AddRef();

	AddComponentToMap(L"COMPONENT_STATE_HANDLER", m_pStateHanderCom = CStateHandler::Create());
	m_pStateHanderCom->AddState(L"IDLE", CStateMonsterIdle::Create());
	m_pStateHanderCom->AddState(L"SEARCH", CStateMonsterSearch::Create(this));

	m_flagColor = false;

	return true;
}

int CMonster::UpdateGameObject()
{
	if (m_bDestroy)
		return OBJ_DEAD;

	m_pStateHanderCom->Request();

	if (typeid(*m_pStateHanderCom->GetCurrentState()) == typeid(CStateMonsterSearch))
		m_flagColor = m_flagColor ? false : true;


	return NOERROR;
}

void CMonster::RenderGameObject()
{
	vec2 position = m_pTransformCom->GetPosition();

	if(m_flagColor)
		g_DC[position.x][position.y] = L'¡ß';
	else
		g_DC[position.x][position.y] = L'¡Þ';

}

void CMonster::ReleaseGameObject()
{
	CGameObject::ReleaseGameObject();

	delete this;
}

bool CMonster::isHit()
{
	m_bDestroy = true;

	return true;
}

void CMonster::Respawn()
{
	CObjectManager::GetInstance()->AddGameObject(L"LAYER_MONSTER", this);
	m_bDestroy = false;
	m_pTransformCom->SetPosition(vec2(m_tOriginPosition.x, m_tOriginPosition.y));
}

CMonster * CMonster::Create(void * _arg)
{
	CMonster* pInstance = new CMonster();
	if (!pInstance->InitializeGameObject(_arg))
		SAFE_DELETE(pInstance);

	return pInstance;
}

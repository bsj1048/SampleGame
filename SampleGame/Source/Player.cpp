#include "stdafx.h"
#include "Player.h"

#include "GameClass.h"
#include "Scene.h"

#include "Mage.h"
#include "Warrior.h"

#include "Navigation.h"

CPlayer::CPlayer(CGameClass* _class)
	:CGameObject()
{
	m_pClass = _class;
}


CPlayer::~CPlayer()
{
}

CPlayer * CPlayer::Create(CGameClass * _class)
{
	CPlayer* pInstance = new CPlayer(_class);
	if (!pInstance->InitializeGameObject(nullptr))
		SAFE_DELETE(pInstance);

	return pInstance;
}

bool CPlayer::InitializeGameObject(void * _arg)
{
	AddComponentToMap(L"COMPONENT_TRANSFORM", m_pTransformCom = dynamic_cast<CTransform*>(CTransform::Create({ 0, 1 }, 1)));

	m_pNavigationCom = CCore::GetInstance()->GetCurrentScene()->GetNavigation();
	AddComponentToMap(L"COMPONENT_NAVIGATION", m_pNavigationCom);
	m_pNavigationCom->AddRef();

	m_nMaxHP = 10;
	m_nHP = m_nMaxHP;
	lstrcpy(m_wszAttackMsg, L"");

	CSubjectManager::GetInstance()->AddData(L"PLAYER_HP", &m_nHP);
	CSubjectManager::GetInstance()->AddData(L"PLAYER_MAXHP", &m_nMaxHP);
	CSubjectManager::GetInstance()->AddData(L"PLAYER_ATTACK", &m_wszAttackMsg);

	CSubjectManager::GetInstance()->Notify(L"PLAYER_HP");
	CSubjectManager::GetInstance()->Notify(L"PLAYER_MAXHP");
	CSubjectManager::GetInstance()->Notify(L"PLAYER_ATTACK");


	return true;
}

int CPlayer::UpdateGameObject()
{
	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_LEFT))
	{
		if(!Attack(vec2(0, -1)))
			m_pTransformCom->MovLeft(m_pNavigationCom);
	}
	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_UP))
	{
		if (!Attack(vec2(-1, 0)))
			m_pTransformCom->MovUp(m_pNavigationCom);
	}
	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_RIGHT))
	{
		if (!Attack(vec2(0, 1)))
			m_pTransformCom->MovRight(m_pNavigationCom);
	}
	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_DOWN))
	{
		if (!Attack(vec2(1, 0)))
			m_pTransformCom->MovDown(m_pNavigationCom);
	}
	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_SPACE))
	{
		if (typeid(*m_pClass) == typeid(CWarrior))
		{
			m_pClass->ReleaseClass();
			m_pClass = CMage::Create();
		}
		else
		{
			m_pClass->ReleaseClass();
			m_pClass = CWarrior::Create();
		}
	}

	return NOERROR;
}

void CPlayer::RenderGameObject()
{
	m_pClass->RenderClass(m_pTransformCom);
}

void CPlayer::ReleaseGameObject()
{
	m_pClass->ReleaseClass();

	CGameObject::ReleaseGameObject();

	delete this;
}

bool CPlayer::Attack(vec2 _direction)
{
	if (m_pClass->Attack(m_pTransformCom, _direction))
	{
		m_nHP = m_nHP - 1 < 0 ? 0 : m_nHP - 1;
		CSubjectManager::GetInstance()->Notify(L"PLAYER_HP");

		m_pClass->GetAttackMsg(m_wszAttackMsg);
		CSubjectManager::GetInstance()->Notify(L"PLAYER_ATTACK");

		return true;
	}

	lstrcpy(m_wszAttackMsg, L"");
	CSubjectManager::GetInstance()->Notify(L"PLAYER_ATTACK");

	return false;
}

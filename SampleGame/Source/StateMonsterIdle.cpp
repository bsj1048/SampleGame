#include "stdafx.h"
#include "StateMonsterIdle.h"


CStateMonsterIdle::CStateMonsterIdle()
{
	m_nTermTime = 100;
}


CStateMonsterIdle::~CStateMonsterIdle()
{
}

void CStateMonsterIdle::Excute()
{
	if (m_nTermTime-- == 0)
	{
		m_pHander->ChangeState(L"SEARCH");

		m_nTermTime = 100;
	}
}

bool CStateMonsterIdle::Enter()
{
	return true;
}

bool CStateMonsterIdle::Exit()
{
	return true;
}

CStateMonsterIdle * CStateMonsterIdle::Create()
{
	return new CStateMonsterIdle;
}

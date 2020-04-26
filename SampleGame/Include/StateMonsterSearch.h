#pragma once

#include "State.h"

class CNavigation;
class CStateMonsterSearch final : public CState
{
private:
	explicit CStateMonsterSearch();
	virtual ~CStateMonsterSearch();
public:
	virtual bool	InitializeState(void* _arg);
public:
	// CState을(를) 통해 상속됨
	virtual void Excute() override;
	virtual bool Enter() override;
	virtual bool Exit() override;
public:
	static CStateMonsterSearch*	Create(CGameObject* _monster);
private:
	CGameObject*	m_pMonster;
};


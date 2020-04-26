#pragma once

#include "State.h"

class CStateMonsterIdle final : public CState
{
private:
	explicit CStateMonsterIdle();
	virtual ~CStateMonsterIdle();
public:
	// CState을(를) 통해 상속됨
	virtual void Excute() override;
	virtual bool Enter() override;
	virtual bool Exit() override;
public:
	static CStateMonsterIdle*	Create();
private:
	int				m_nTermTime;
};


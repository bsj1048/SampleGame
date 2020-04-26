#pragma once

#include "StateHandler.h"

class CState abstract
{
protected:
	explicit CState();
	virtual ~CState();
public:
	virtual bool	InitializeState(void* _arg);
	virtual void	ReleaseState();
public:
	void	SetHandler(CStateHandler* _handler) { m_pHander = _handler; };
public:
	virtual void	Excute() PURE;
	virtual bool	Enter() PURE;
	virtual bool	Exit() PURE;
protected:
	CStateHandler*	m_pHander;
};


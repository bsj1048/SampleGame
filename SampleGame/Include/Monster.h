#pragma once

#include "GameObject.h"

class CNavigation;
class CStateHandler;
class CMonster final : public CGameObject
{
private:
	explicit CMonster();
	virtual ~CMonster();
public:
	// CGameObject을(를) 통해 상속됨
	virtual bool InitializeGameObject(void * _arg) override;
	virtual int UpdateGameObject() override;
	virtual void RenderGameObject() override;
	virtual void ReleaseGameObject() override;
public:
	virtual bool	isHit();
	virtual void	Respawn();
public:
	static CMonster*	Create(void* _arg);
private:
	vec2			m_tOriginPosition;
	CNavigation*	m_pNavigationCom;
	CStateHandler*	m_pStateHanderCom;
private:
	bool		m_flagColor;
};


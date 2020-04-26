#pragma once

#include "GameObject.h"

class CGameClass;
class CNavigation;
class CPlayer final : public CGameObject
{
private:
	explicit CPlayer(CGameClass* _class);
	virtual ~CPlayer();
public:
	// CGameObject을(를) 통해 상속됨
	virtual bool InitializeGameObject(void * _arg) override;
	virtual int UpdateGameObject() override;
	virtual void RenderGameObject() override;
	virtual void ReleaseGameObject() override;
public:
	bool	Attack(vec2 _direction);
public:
	static CPlayer* Create(CGameClass* _class);
private:
	CNavigation*	m_pNavigationCom; // do not release here
	CGameClass*		m_pClass;
private:
	int		m_nHP;
	int		m_nMaxHP;

	wchar_t m_wszAttackMsg[20];
};


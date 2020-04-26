#pragma once

#include "Component.h"

class CObserver final : public CComponent
{
private:
	explicit CObserver();
	virtual ~CObserver();
public:
	virtual bool	InitializeComponent() override;
	virtual void	ReleaseComponent() override;
public:
	int		UpdateObserver(const wchar_t* _tag);
public:
	const wchar_t*	GetAttackMsg() { return m_wszAttackMsg; };
	int		GetHP() { return m_nHP; };
	int		GetMaxHP() { return m_nMaxHP; };
public:
	static CObserver*	Create();
private:
	int m_nHP;
	int m_nMaxHP;

	wchar_t m_wszAttackMsg[20];
};


#pragma once

#include "Component.h"

class CState;
class CStateHandler final : public CComponent
{
private:
	explicit CStateHandler();
	virtual ~CStateHandler();
public:
	virtual bool	InitializeComponent() override;
	virtual void	ReleaseComponent() override;
public:
	CState*		GetCurrentState() { return m_pCurrentState; };
public:
	void	Request();
	bool	AddState(const wchar_t* _stateTag, CState* _state);
	bool	ChangeState(const wchar_t* _stateTag);
public:
	static CStateHandler* Create();
private:
	map<const wchar_t*, CState*>			m_mapStates;
	typedef map<const wchar_t*, CState*>	STATEMAP;
private:
	CState*		m_pCurrentState;
};


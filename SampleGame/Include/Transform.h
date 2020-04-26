#pragma once

#include "Component.h"

class CNavigation;
class CTransform final : public CComponent
{
public:
	explicit CTransform();
	virtual ~CTransform();
public:
	virtual bool	InitializeComponent() override;
	virtual bool	InitializeComponent(vec2 _position, int _speed);
	virtual void	ReleaseComponent() override;;
public:
	const vec2&	GetPosition() { return m_tPosition; }
public:
	void		SetPosition(vec2 _position) { m_tPosition = _position; }
public:
	void		MovLeft(CNavigation* _navigation);
	void		MovUp(CNavigation* _navigation);
	void		MovRight(CNavigation* _navigation);
	void		MovDown(CNavigation* _navigation);
public:
	static	CTransform* Create(vec2 _position, int _speed);
private:
	vec2	m_tPosition;
	int		m_nSpeed;
};


#pragma once

class CTransform;
class CGameClass abstract
{
protected:
	explicit CGameClass();
	virtual ~CGameClass();
public:
	virtual bool	InitializeClass(void* _arg) PURE;
	virtual void	RenderClass(CTransform* _transform) PURE;
	virtual void	ReleaseClass() PURE;
public:
	virtual void	GetAttackMsg(wchar_t* _msg) PURE;
public:
	virtual bool	Attack(CTransform * _transform, vec2 _direction) PURE;
};


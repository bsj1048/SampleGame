#pragma once

#include "Transform.h"

class CGameObject abstract
{
protected:
	explicit CGameObject();
	virtual ~CGameObject();
public:
	virtual bool	InitializeGameObject(void* _arg)	PURE;
	virtual int		UpdateGameObject()					PURE;
	virtual void	RenderGameObject()					PURE;
	virtual void	ReleaseGameObject()					PURE;
public:
	CComponent*		GetComponent(const wchar_t* _componentTag);
public:
	bool	AddComponentToMap(const wchar_t* _componentTag, CComponent* _component);
public:
	virtual bool	isHit();
	virtual	void	Respawn();
protected:
	map<const wchar_t*, CComponent*>	m_mapComponents;
protected:
	CTransform*							m_pTransformCom;
protected:
	bool		m_bDestroy;
};


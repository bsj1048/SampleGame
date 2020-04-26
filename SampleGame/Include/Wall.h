#pragma once

#include "GameObject.h"

class CWall final : CGameObject
{
private:
	explicit CWall();
	virtual ~CWall();
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual bool	InitializeGameObject(void* _arg)	override;
	virtual int		UpdateGameObject()		override;
	virtual void	RenderGameObject()		override;
	virtual void	ReleaseGameObject()		override;
public:
	static	CGameObject*	Create(void* _arg = nullptr);
};


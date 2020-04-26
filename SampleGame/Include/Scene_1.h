#pragma once

#include "Scene.h"

class CGameObject;
class CScene_1 final : public CScene
{
private:
	explicit CScene_1();
	virtual ~CScene_1();
public:
	// CScene��(��) ���� ��ӵ�
	virtual bool	InitializeScene()	override;
	virtual int		UpdateScene() override;
	virtual void	RenderScene() override;
	virtual void	ReleaseScene() override;
public:
	static	CScene_1* Create();
private:
	// CScene��(��) ���� ��ӵ�
	virtual void ClearDC() override;
private:
	const int	m_nCX = 6;
	const int	m_nCY = 10;
};


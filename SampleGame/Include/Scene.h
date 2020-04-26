#pragma once

class CGameObject;
class CNavigation;
class CScene abstract
{
protected:
	explicit CScene();
	virtual ~CScene();
public:
	virtual bool	InitializeScene()	PURE;
	virtual int		UpdateScene()		PURE;
	virtual void	RenderScene()		PURE;
	virtual void	ReleaseScene()		PURE;
public:
	int				GetSceneNO() { return m_nSceneNO; };
	CNavigation*	GetNavigation() { return m_pNavigationCom; };
protected:
	virtual void	ClearDC() PURE;
protected:
	int				m_nSceneNO;
protected:
	CNavigation*		m_pNavigationCom;
};


#pragma once

#include "KeyBoardManager.h"
#include "ObjectManager.h"
#include "RespawnManager.h"
#include "UIManager.h"
#include "SubjectManager.h"

class CScene;
class CCore final
{
private:
	explicit CCore();
	virtual ~CCore() = default;

	DECLARE_SINGLETON(CCore);

public:
	bool	Initialize();
	int		Update();
	void	Render();
	void	Release();
public:
	CScene*		GetCurrentScene() { return m_pCurrentScene; };
public:
	bool		SceneChanged(CScene* _scene);
private:
	CKeyBoardManager*		m_pKeyBoardMgr;
	CObjectManager*			m_pObjectMgr;
	CRespawnManager*		m_pRespawnMgr;
	CSubjectManager*		m_pSubjectMgr;
	CUIManager*				m_pUIMgr;
private:
	int					m_nCurrentSceneNO;
	CScene*				m_pCurrentScene;

	int					m_nEvent;
};


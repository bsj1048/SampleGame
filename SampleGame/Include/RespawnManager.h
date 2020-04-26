#pragma once


class CGameObject;
class CRespawnManager final
{
public:
	typedef struct tagRespawn
	{
		int				nTerm = 10;
		CGameObject*	pObject;
	} RESPAWN_INFO;
public:
	CRespawnManager();
	~CRespawnManager();

	DECLARE_SINGLETON(CRespawnManager)

public:
	bool	Initialize();
	int		Update();
	void	Release();
public:
	void		AddInfo(RESPAWN_INFO _info);
private:
	list<RESPAWN_INFO>		m_lstInfoes;
	typedef	list<RESPAWN_INFO>	INFOLST;
};


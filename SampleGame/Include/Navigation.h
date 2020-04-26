#pragma once

#include "Component.h"
#include "Cell.h"

class CNavigation final : public CComponent
{
public:
	typedef struct tagSearchInfo
	{
		tagSearchInfo*	pParent;
		vec2			tPosition;
		float			fCost;
	} SEARCH_INFO;
private:
	CNavigation();
	~CNavigation();
public:
	virtual bool	InitializeComponent() override;
	virtual bool	InitializeComponent(int _CX, int _CY, vec2* _walls, size_t _size);
	virtual void	ReleaseComponent() override;
public:
	void	AddRef() { ++m_nReferenceCnt; };
public:
	bool		CheckMove(vec2	_postPosition);
	vec2		SearchingMove(vec2 _start, vec2 _end);
public:
	static	CNavigation* Create(int _CX, int _CY, vec2* _walls, size_t _size);
private:
	bool			FindPath(SEARCH_INFO* _start, SEARCH_INFO* _end, vector<vector<bool>>* _cells);
	vector<vec2>	MakePath();
	bool			isInOpenedLst(SEARCH_INFO _info);
	bool			isInClosedLst(SEARCH_INFO _info);
private:
	int		m_nCX;
	int		m_nCY;
private:
	vector<vector<CCell*>>		m_vecCells;
	static	unsigned int		m_nReferenceCnt;
private: // for A*
	list<SEARCH_INFO*>			m_lstInfoes;
	list<SEARCH_INFO*>			m_lstOpened;
	list<SEARCH_INFO*>			m_lstClosed;
};


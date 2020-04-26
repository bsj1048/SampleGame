#include "stdafx.h"
#include "Navigation.h"

#include "GameObject.h"

unsigned int CNavigation::m_nReferenceCnt = 0;

CNavigation::CNavigation()
{
}


CNavigation::~CNavigation()
{
}

bool CNavigation::InitializeComponent()
{
	return true;
}

bool CNavigation::InitializeComponent(int _CX, int _CY, vec2 * _walls, size_t _size)
{
	m_vecCells.resize(_CX);
	for (int i = 0; i < _CX; ++i)
	{
		m_vecCells[i].resize(_CY);
	}

	for (size_t i = 0; i < m_vecCells.size(); ++i)
	{
		for (size_t j = 0; j < m_vecCells[i].size(); ++j)
		{
			m_vecCells[i][j] = CCell::Create(i, j);
		}
	}

	for (size_t i = 0; i < _size; ++i)
	{
		m_vecCells[_walls[i].x][_walls[i].y]->SetBlock(true);
	}

	m_nCX = _CX;
	m_nCY = _CY;

	return true;
}

void CNavigation::ReleaseComponent()
{
	if (m_nReferenceCnt-- == 0)
	{
		for (size_t i = 0; i < m_vecCells.size(); ++i)
		{
			for (size_t j = 0; j < m_vecCells[i].size(); ++j)
			{
				m_vecCells[i][j]->ReleaseCell();
			}
			m_vecCells[i].clear();
		}
		m_vecCells.clear();

		for (auto& element : m_lstInfoes)
			SAFE_DELETE(element);
		m_lstInfoes.clear();
		m_lstOpened.clear();
		m_lstClosed.clear();

		delete this;
	}

}

bool CNavigation::CheckMove(vec2 _postPosition)
{
	if (_postPosition.x < 0 || _postPosition.x >= m_nCX)
		return false;

	if (_postPosition.y < 0 || _postPosition.y >= m_nCY)
		return false;

	return !m_vecCells[_postPosition.x][_postPosition.y]->isBlock();
}

vec2 CNavigation::SearchingMove(vec2 _start, vec2 _end)
{
	vec2 ret = { -1, -1 };
	vector<vec2> vecPath;
	if (_start == _end)
		return ret;

	vector<vector<bool>> vecBools;
	vecBools.resize(m_vecCells.size());
	for (size_t i = 0; i < m_vecCells.size(); ++i)
	{
		vecBools[i].resize(m_vecCells[i].size());
	}

	for (size_t i = 0; i < m_vecCells.size(); ++i)
	{
		for (size_t j = 0; j < m_vecCells[i].size(); ++j)
		{
			vecBools[i][j] = m_vecCells[i][j]->isBlock();
		}
	}

	SEARCH_INFO* startInfo = new SEARCH_INFO;
	startInfo->fCost = 0.0f;
	startInfo->pParent = nullptr;
	startInfo->tPosition = _start;

	SEARCH_INFO* endInfo = new SEARCH_INFO;
	endInfo->fCost = 0.0f;
	endInfo->pParent = nullptr;
	endInfo->tPosition = _end;

	for (auto& element : m_lstInfoes)
		SAFE_DELETE(element);
	m_lstInfoes.clear();
	m_lstOpened.clear();
	m_lstClosed.clear();

	m_lstInfoes.push_back(startInfo);
	m_lstInfoes.push_back(endInfo);


	if (FindPath(m_lstInfoes.front(), m_lstInfoes.back(), &vecBools))
	{
		vecPath = MakePath();
		ret = vecPath.back();
	}


	return ret;
}


CNavigation * CNavigation::Create(int _CX, int _CY, vec2* _walls, size_t _size)
{
	CNavigation* pInstance = new CNavigation();
	if (!pInstance->InitializeComponent(_CX, _CY, _walls, _size))
		SAFE_DELETE(pInstance);

	return pInstance;
}

bool CNavigation::FindPath(SEARCH_INFO* _start, SEARCH_INFO* _end, vector<vector<bool>>* _cells)
{
	if (!m_lstOpened.empty())
		m_lstOpened.pop_front();

	m_lstClosed.push_back(_start);


	SEARCH_INFO aroundInfo;
	if (_start->tPosition == _end->tPosition)
		return true;

	// left
	aroundInfo.tPosition = _start->tPosition;
	aroundInfo.tPosition.y -= 1;
	if (aroundInfo.tPosition.y >= 0 && !_cells->at(aroundInfo.tPosition.x)[aroundInfo.tPosition.y])
	{
		if (!isInOpenedLst(aroundInfo) && !isInClosedLst(aroundInfo))
		{
			SEARCH_INFO* leftInfo = new SEARCH_INFO;
			leftInfo->tPosition = aroundInfo.tPosition;
			leftInfo->pParent = _start;
			leftInfo->fCost = sqrtf(powf(fabsf(float(leftInfo->tPosition.x - _end->tPosition.x)), 2) + powf(fabsf(float(leftInfo->tPosition.y - _end->tPosition.y)), 2)) + 1;
			m_lstOpened.push_back(leftInfo);
			m_lstInfoes.push_back(leftInfo);
		}
	}
	// up
	aroundInfo.tPosition = _start->tPosition;
	aroundInfo.tPosition.x -= 1;
	if (aroundInfo.tPosition.x >= 0 && !_cells->at(aroundInfo.tPosition.x)[aroundInfo.tPosition.y])
	{
		if (!isInOpenedLst(aroundInfo) && !isInClosedLst(aroundInfo))
		{
			SEARCH_INFO* upInfo = new SEARCH_INFO;
			upInfo->tPosition = aroundInfo.tPosition;
			upInfo->pParent = _start;
			upInfo->fCost = sqrtf(powf(fabsf(float(upInfo->tPosition.x - _end->tPosition.x)), 2) + powf(fabsf(float(upInfo->tPosition.y - _end->tPosition.y)), 2)) + 1;
			m_lstOpened.push_back(upInfo);
			m_lstInfoes.push_back(upInfo);
		}
	}
	// right
	aroundInfo.tPosition = _start->tPosition;
	aroundInfo.tPosition.y += 1;
	if (size_t(aroundInfo.tPosition.y) < _cells->at(0).size() && !_cells->at(aroundInfo.tPosition.x)[aroundInfo.tPosition.y])
	{
		if (!isInOpenedLst(aroundInfo) && !isInClosedLst(aroundInfo))
		{
			SEARCH_INFO* rightInfo = new SEARCH_INFO;
			rightInfo->tPosition = aroundInfo.tPosition;
			rightInfo->pParent = _start;
			rightInfo->fCost = sqrtf(powf(fabsf(float(rightInfo->tPosition.x - _end->tPosition.x)), 2) + powf(fabsf(float(rightInfo->tPosition.y - _end->tPosition.y)), 2)) + 1;
			m_lstOpened.push_back(rightInfo);
			m_lstInfoes.push_back(rightInfo);
		}
	}
	// down
	aroundInfo.tPosition = _start->tPosition;
	aroundInfo.tPosition.x += 1;
	if (size_t(aroundInfo.tPosition.x) < _cells->size() && !_cells->at(aroundInfo.tPosition.x)[aroundInfo.tPosition.y])
	{
		if (!isInOpenedLst(aroundInfo) && !isInClosedLst(aroundInfo))
		{
			SEARCH_INFO* downInfo = new SEARCH_INFO;
			downInfo->tPosition = aroundInfo.tPosition;
			downInfo->pParent = _start;
			downInfo->fCost = sqrtf(powf(fabsf(float(downInfo->tPosition.x - _end->tPosition.x)), 2) + powf(fabsf(float(downInfo->tPosition.y - _end->tPosition.y)), 2)) + 1;
			m_lstOpened.push_back(downInfo);
			m_lstInfoes.push_back(downInfo);
		}
	}

	if (m_lstOpened.empty())
		return false;

	m_lstOpened.sort([](SEARCH_INFO* _operand1, SEARCH_INFO* _operand2)->bool {
		return _operand1->fCost < _operand2->fCost;
	});

	return FindPath(m_lstOpened.front(), _end, _cells);
}

vector<vec2> CNavigation::MakePath()
{
	vector<vec2> retPath;

	SEARCH_INFO* current = m_lstInfoes.back();

	while (current->pParent)
	{
		retPath.push_back(current->tPosition);
		current = current->pParent;
	}

	return retPath;
}

bool CNavigation::isInOpenedLst(SEARCH_INFO _info)
{
	auto found = find_if(m_lstOpened.begin(), m_lstOpened.end(), [_info](SEARCH_INFO* _operand)->bool{
		return _operand->tPosition == _info.tPosition;
	});

	if (found != m_lstOpened.end())
		return true;

	return false;
}

bool CNavigation::isInClosedLst(SEARCH_INFO _info)
{
	auto found = find_if(m_lstClosed.begin(), m_lstClosed.end(), [_info](SEARCH_INFO* _operand)->bool {
		return _operand->tPosition == _info.tPosition;
	});

	if (found != m_lstClosed.end())
		return true;

	return false;
}

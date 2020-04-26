#include "stdafx.h"
#include "Cell.h"


CCell::CCell()
{
}

CCell::~CCell()
{
}

bool CCell::InitializeCell(int _x, int _y)
{
	m_nX = _x;
	m_nY = _y;
	m_bBlock = false;

	return true;
}

void CCell::ReleaseCell()
{
	delete this;
}

CCell * CCell::Create(int _x, int _y)
{
	CCell* pInstance = new CCell;
	if (!pInstance->InitializeCell(_x, _y))
		SAFE_DELETE(pInstance);

	return pInstance;
}

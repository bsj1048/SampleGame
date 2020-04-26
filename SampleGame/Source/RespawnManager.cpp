#include "stdafx.h"
#include "RespawnManager.h"

#include "GameObject.h"

IMPLEMENT_SINGLETON(CRespawnManager)

CRespawnManager::CRespawnManager()
{
	Initialize();
}


CRespawnManager::~CRespawnManager()
{
	Release();
}

bool	CRespawnManager::Initialize()
{
	return true;
}

int CRespawnManager::Update()
{
	INFOLST::iterator iter;
	INFOLST::iterator iter_end = m_lstInfoes.end();

	for (iter = m_lstInfoes.begin(); iter != iter_end; )
	{
		if ((*iter).nTerm-- == 0)
		{
			(*iter).pObject->Respawn();
			iter = m_lstInfoes.erase(iter);
		}
		else
			iter++;
	}

	return NOERROR;
}

void CRespawnManager::Release()
{
	for (auto info : m_lstInfoes)
		info.pObject->ReleaseGameObject();
	m_lstInfoes.clear();
}

void CRespawnManager::AddInfo(RESPAWN_INFO _info)
{
	m_lstInfoes.push_back(_info);
}

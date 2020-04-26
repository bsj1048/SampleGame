#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"

IMPLEMENT_SINGLETON(CObjectManager)

CObjectManager::CObjectManager()
{
	Initialize();
}


CObjectManager::~CObjectManager()
{
	Release();
}

bool	CObjectManager::Initialize()
{
	return true;
}

int CObjectManager::Update()
{
	int eventMsg = NOERROR;

	for (auto& pair : m_mapLayers)
	{
		OBJECTLST::iterator iter;
		OBJECTLST::iterator iter_end = pair.second.end();

		for (iter = pair.second.begin(); iter != iter_end; )
		{
			eventMsg = (*iter)->UpdateGameObject();
			if (eventMsg == OBJ_DEAD)
			{
				CRespawnManager::RESPAWN_INFO info;
				info.nTerm = 10;
				info.pObject = *iter;
				CRespawnManager::GetInstance()->AddInfo(info);
				iter = pair.second.erase(iter);
			}
			else
				iter++;
		}
	}


	return NOERROR;
}

void CObjectManager::Render()
{
	for (auto pair : m_mapLayers)
	{
		for (auto object : pair.second)
		{
			object->RenderGameObject();
		}
	}
}

void CObjectManager::Release()
{
	for (auto pair : m_mapLayers)
	{
		for (auto object : pair.second)
		{
			object->ReleaseGameObject();
		}
		pair.second.clear();
	}
	m_mapLayers.clear();
}

bool CObjectManager::AddGameObject(const wchar_t* _layerTag, CGameObject* _object)
{
	if (!m_pInstance)
		return false;

	auto found = find_if(m_mapLayers.begin(), m_mapLayers.end(), CFuntor(_layerTag));

	if (found != m_mapLayers.end())
	{
		found->second.push_back(_object);
		return true;
	}

	list<CGameObject*> list;
	list.push_back(_object);
	m_mapLayers.insert(LAYERMAP::value_type(_layerTag, list));

	return true;
}

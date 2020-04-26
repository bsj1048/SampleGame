#include "stdafx.h"
#include "SubjectManager.h"

#include "Observer.h"

IMPLEMENT_SINGLETON(CSubjectManager)

CSubjectManager::CSubjectManager()
{
	Initialize();
}


CSubjectManager::~CSubjectManager()
{
	Release();
}

bool CSubjectManager::Initialize()
{
	return true;
}

void CSubjectManager::Release()
{
	m_mapDatas.clear();
	m_lstObservers.clear();
}

void	CSubjectManager::AddData(const wchar_t* _dataTag, void* _data)
{
	m_mapDatas.insert(DATAMAP::value_type(_dataTag, _data));
}

void	CSubjectManager::Notify(const wchar_t* _tag)
{
	for (auto observer : m_lstObservers)
	{
		observer->UpdateObserver(_tag);
	}
}

void CSubjectManager::Subscribe(CObserver * _observer)
{
	auto found = find(m_lstObservers.begin(), m_lstObservers.end(), _observer);

	if (found != m_lstObservers.end())
		return;

	m_lstObservers.push_back(_observer);
}


void CSubjectManager::UnSubscribe(CObserver * _observer)
{
	auto& found = find(m_lstObservers.begin(), m_lstObservers.end(), _observer);

	if (found == m_lstObservers.end())
		return;

	m_lstObservers.erase(found);
}

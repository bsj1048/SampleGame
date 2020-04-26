#include "stdafx.h"
#include "Observer.h"

#include "SubjectManager.h"

CObserver::CObserver()
{
}


CObserver::~CObserver()
{
}

bool CObserver::InitializeComponent()
{
	return true;
}

int CObserver::UpdateObserver(const wchar_t * _tag)
{
	void* data = CSubjectManager::GetInstance()->GetData(_tag);

	if (!lstrcmp(L"PLAYER_HP", _tag))
		m_nHP = *(int*)data;
	else 	if (!lstrcmp(L"PLAYER_MAXHP", _tag))
		m_nMaxHP = *(int*)data;
	else 	if (!lstrcmp(L"PLAYER_ATTACK", _tag))
		lstrcpy(m_wszAttackMsg, (wchar_t*)data);

	return NOERROR;
}

CObserver * CObserver::Create()
{
	CObserver* pInstance = new CObserver();
	if (!pInstance->InitializeComponent())
		SAFE_DELETE(pInstance);

	return pInstance;
}

void CObserver::ReleaseComponent()
{
	CSubjectManager::GetInstance()->UnSubscribe(this);

	delete this;
}

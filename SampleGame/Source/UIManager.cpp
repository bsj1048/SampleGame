#include "stdafx.h"
#include "UIManager.h"

#include "Observer.h"

IMPLEMENT_SINGLETON(CUIManager)

CUIManager::CUIManager()
{
	m_pObserver = CObserver::Create();

	CSubjectManager::GetInstance()->Subscribe(m_pObserver);
}


CUIManager::~CUIManager()
{
	m_pObserver->ReleaseComponent();
}

int CUIManager::Update()
{
	return NOERROR;
}

void CUIManager::Render()
{
	int nHP = m_pObserver->GetHP();
	int nMaxHP = m_pObserver->GetMaxHP();

	cout << nHP << " / " << nMaxHP << endl;

	wcout << m_pObserver->GetAttackMsg() << endl;
}

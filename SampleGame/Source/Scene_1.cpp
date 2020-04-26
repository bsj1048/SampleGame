#include "stdafx.h"
#include "ObjectManager.h"

#include "Scene_1.h"
#include "GameObject.h"
#include "Navigation.h"
#include "Wall.h"
#include "Monster.h"

CScene_1::CScene_1()
{
}


CScene_1::~CScene_1()
{
}

bool CScene_1::InitializeScene()
{
	m_nSceneNO = 1;

	g_DC.clear();
	g_DC.resize(m_nCX);
	for(int i = 0; i < m_nCX; ++i)
		g_DC[i].resize(m_nCY);

	vec2 arrPosition[] = {
		{ 0, 0 },{ 0, 2 },{ 0, 3 },{ 0, 4 },{ 0, 5 },{ 0, 6 },{ 0, 7 },{ 0, 8 },{ 0, 9 },
		{ 1, 0 },{ 1, 9 },
		{ 2, 0 },{ 2, 2 },{ 2, 3 },{ 2, 4 },{ 2, 5 },{ 2, 9 },
		{ 3, 0 },{ 3, 5 },{ 3, 6 },{ 3, 9 },
		{ 4, 0 },{ 4, 1 },{ 4, 9 },
		{ 5, 0 },{ 5, 1 },{ 5, 2 },{ 5, 3 },{ 5, 4 },{ 5, 5 },{ 5, 6 },{ 5, 7 },{ 5, 9 },
	};

	m_pNavigationCom = CNavigation::Create(m_nCX, m_nCY, arrPosition, sizeof(arrPosition)/ sizeof(arrPosition[0]));

	CObjectManager* objMgr = CObjectManager::GetInstance();
	
	for (auto position : arrPosition)
		objMgr->AddGameObject(L"LAYER_WALL", CWall::Create(&vec2(position.x, position.y)));

	return true;
}

int CScene_1::UpdateScene()
{
	CObjectManager::GetInstance()->Update();

	return NOERROR;
}

void CScene_1::RenderScene()
{
	ClearDC();

	CObjectManager::GetInstance()->Render();

	for (int i = 0; i < m_nCX; ++i)
	{
		for (int j = 0; j < m_nCY; ++j)
		{
			if (g_DC[i][j] == L' ')
				wcout << L"  ";
			else
				wcout << g_DC[i][j];
		}
		cout << endl;
	}

}

void CScene_1::ReleaseScene()
{
	m_pNavigationCom->ReleaseComponent();

	delete this;
}

CScene_1* CScene_1::Create()
{
	CScene_1* pInstance = new CScene_1();
	if (!pInstance->InitializeScene())
		SAFE_DELETE(pInstance);

	return pInstance;
}

void CScene_1::ClearDC()
{
	system("cls");

	for (int i = 0; i < m_nCX; ++i)
	{
		for (int j = 0; j < m_nCY; ++j)
			g_DC[i][j] =  L' ';
	}
}


#include "stdafx.h"
#include "Core.h"

#include "SceneTitle.h"
#include "Scene_1.h"

vector<vector<wchar_t>>	g_DC; // where console draws

IMPLEMENT_SINGLETON(CCore)

CCore::CCore()
	: m_pKeyBoardMgr(nullptr)
	, m_pObjectMgr(nullptr)
	, m_pRespawnMgr(nullptr)
	, m_pSubjectMgr(nullptr)
	, m_pUIMgr(nullptr)
	, m_pCurrentScene(nullptr)
{
}

bool CCore::Initialize()
{
	// for being enable wcout and hiding cursor
	wcout.imbue(locale("kor"));
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);


	m_pKeyBoardMgr = CKeyBoardManager::GetInstance();
	m_pObjectMgr = CObjectManager::GetInstance();
	m_pRespawnMgr = CRespawnManager::GetInstance();
	m_pSubjectMgr = CSubjectManager::GetInstance();
	m_pUIMgr = CUIManager::GetInstance();

	m_pCurrentScene = CSceneTitle::Create();
	m_nCurrentSceneNO = m_pCurrentScene->GetSceneNO();
	
	return true;
}

int CCore::Update()
{
	m_nEvent = NOERROR;

	m_pKeyBoardMgr->Update();
	m_pRespawnMgr->Update();

	m_nEvent = m_pCurrentScene->UpdateScene();

	if(m_nCurrentSceneNO > 0)
		m_pUIMgr->Update();

	return NOERROR;
}

void CCore::Render()
{
	if (m_nEvent == SCENE_CHANGED)
		return;

	m_pCurrentScene->RenderScene();

	if (m_nCurrentSceneNO > 0)
		m_pUIMgr->Render();
}

void CCore::Release()
{
	m_pCurrentScene->ReleaseScene();

	m_pKeyBoardMgr->DestroyInstance();
	m_pObjectMgr->DestroyInstance();
	m_pRespawnMgr->DestroyInstance();
	m_pUIMgr->DestroyInstance();
	m_pSubjectMgr->DestroyInstance();

	delete this;
}

bool CCore::SceneChanged(CScene * _scene)
{
	if (!_scene)
		return false;

	m_pCurrentScene->ReleaseScene();

	m_pCurrentScene = _scene;
	m_nCurrentSceneNO = m_pCurrentScene->GetSceneNO();

	return true;
}

#include "stdafx.h"
#include "SceneTitle.h"
#include "Scene_1.h"

#include "Warrior.h"
#include "Mage.h"
#include "Player.h"
#include "Monster.h"

CSceneTitle::CSceneTitle()
{
}


CSceneTitle::~CSceneTitle()
{
}

bool CSceneTitle::InitializeScene()
{
	m_nSceneNO = 0;
	m_nCurrentMsgNO = 0;

	return true;
}

int CSceneTitle::UpdateScene()
{
	int select = 0;

	if (CKeyBoardManager::GetInstance()->isKeyDown(KEY_RETURN) && m_nCurrentMsgNO < 3)
		m_nCurrentMsgNO++;

	if (m_nCurrentMsgNO > 3)
	{
		cin >> select;
		CCore::GetInstance()->SceneChanged(CScene_1::Create());

		CPlayer* pPlayer = nullptr;
		if (select == 1)
			pPlayer = CPlayer::Create(CWarrior::Create());
		else if (select == 2)
			pPlayer = CPlayer::Create(CMage::Create());
		CObjectManager::GetInstance()->AddGameObject(L"LAYER_PLAYER", pPlayer);

		CObjectManager::GetInstance()->AddGameObject(L"LAYER_MONSTER", CMonster::Create(&vec2(2, 7)));
		CObjectManager::GetInstance()->AddGameObject(L"LAYER_MONSTER", CMonster::Create(&vec2(4, 4)));
		CObjectManager::GetInstance()->AddGameObject(L"LAYER_MONSTER", CMonster::Create(&vec2(1, 8)));

		return SCENE_CHANGED;
	}

	return NOERROR;
}

void CSceneTitle::RenderScene()
{
	ClearDC();

	switch (m_nCurrentMsgNO)
	{
	case 1:
		wcout << m_wszMessage1 << endl;
		break;
	case 2:
		wcout << m_wszMessage2 << endl;
		break;
	case 3:
		wcout << m_wszMessage2 << endl;
		m_nCurrentMsgNO++;
		wcout << m_wszMessage3 << endl;
		break;
	}
}

void CSceneTitle::ReleaseScene()
{
	delete this;
}

CSceneTitle * CSceneTitle::Create()
{
	CSceneTitle* pInstance = new CSceneTitle();
	if (!pInstance->InitializeScene())
		SAFE_DELETE(pInstance);

	return pInstance;
}

void CSceneTitle::ClearDC()
{
	system("cls");
}

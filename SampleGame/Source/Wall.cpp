#include "stdafx.h"
#include "Wall.h"


CWall::CWall()
{
}


CWall::~CWall()
{
}

bool CWall::InitializeGameObject(void* _arg)
{
	vec2 position = *(vec2*)_arg;

	AddComponentToMap(L"COMPONENT_TRANSFORM", m_pTransformCom = CTransform::Create({ position.x, position.y }, 0));

	return true;
}

int CWall::UpdateGameObject()
{
	return NOERROR;
}

void CWall::RenderGameObject()
{
	vec2 position = m_pTransformCom->GetPosition();

	g_DC[position.x][position.y] = L'¢Ç';
}

void CWall::ReleaseGameObject()
{
	CGameObject::ReleaseGameObject();

	delete this;
}

CGameObject * CWall::Create(void* _arg)
{
	CWall* pInstance = new CWall();
	if (!pInstance->InitializeGameObject(_arg))
		SAFE_DELETE(pInstance);

	return pInstance;
}

#include "stdafx.h"
#include "Warrior.h"

#include "GameObject.h"
#include "Transform.h"

CWarrior::CWarrior()
{
}


CWarrior::~CWarrior()
{
}

bool CWarrior::InitializeClass(void * _arg)
{
	return true;
}

void CWarrior::RenderClass(CTransform * _transform)
{
	vec2 position = _transform->GetPosition();

	g_DC[position.x][position.y] = L'◎';
}

void CWarrior::ReleaseClass()
{
	delete this;
}


CWarrior * CWarrior::Create(void* _arg)
{
	CWarrior* pInstance = new CWarrior();
	if (!pInstance->InitializeClass(_arg))
		SAFE_DELETE(pInstance);

	return pInstance;
}

void CWarrior::GetAttackMsg(wchar_t * _msg)
{
	lstrcpy(_msg, L"전사의 공격");
}

bool CWarrior::Attack(CTransform * _transform, vec2 _direction)
{
	vec2 position = _transform->GetPosition();

	position.x += _direction.x;
	position.y += _direction.y;

	for (auto object : CObjectManager::GetInstance()->GetLayer(L"LAYER_MONSTER"))
	{
		CTransform* monsterTransform = dynamic_cast<CTransform*>(object->GetComponent(L"COMPONENT_TRANSFORM"));
		if (monsterTransform->GetPosition() == position)
		{
			object->isHit();
			return true;
		}
	}

	return false;
}

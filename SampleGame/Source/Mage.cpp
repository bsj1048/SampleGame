#include "stdafx.h"
#include "Mage.h"


#include "Transform.h"
#include "GameObject.h"

CMage::CMage()
{
}


CMage::~CMage()
{
}

bool CMage::InitializeClass(void * _arg)
{
	return true;
}

void CMage::RenderClass(CTransform * _transform)
{
	vec2 position = _transform->GetPosition();

	g_DC[position.x][position.y] = L'☆';
}

void CMage::ReleaseClass()
{
	delete this;
}

void CMage::GetAttackMsg(wchar_t * _msg)
{
	lstrcpy(_msg, L"마법사의 공격");
}

bool CMage::Attack(CTransform * _transform, vec2 _direction)
{
	vec2 position = { 0, 0 };

	for (auto object : CObjectManager::GetInstance()->GetLayer(L"LAYER_MONSTER"))
	{
		CTransform* monsterTransform = dynamic_cast<CTransform*>(object->GetComponent(L"COMPONENT_TRANSFORM"));
		for (int i = 0; i < 2; ++i)
		{
			position = _transform->GetPosition();

			position.x += (_direction.x * (i + 1));
			position.y += (_direction.y * (i + 1));

			if (monsterTransform->GetPosition() == position)
			{
				object->isHit();
				return true;
			}
		}
	}

	return false;
}


CMage * CMage::Create(void * _arg)
{
	CMage* pInstance = new CMage();
	if (!pInstance->InitializeClass(_arg))
		SAFE_DELETE(pInstance);

	return pInstance;
}

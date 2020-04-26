#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	:m_bDestroy(false)
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::ReleaseGameObject()
{
	for (auto pair : m_mapComponents)
		pair.second->ReleaseComponent();
	m_mapComponents.clear();
}

CComponent * CGameObject::GetComponent(const wchar_t * _componentTag)
{
	auto found = find_if(m_mapComponents.begin(), m_mapComponents.end(), CFuntor(_componentTag));

	if (found == m_mapComponents.end())
		return nullptr;

	return found->second;
}

bool CGameObject::AddComponentToMap(const wchar_t * _componentTag, CComponent * _component)
{
	auto found = find_if(m_mapComponents.begin(), m_mapComponents.end(), CFuntor(_componentTag));

	if (found != m_mapComponents.end())
		return false;

	m_mapComponents.insert(map<const wchar_t*, CComponent*>::value_type(_componentTag, _component));

	return true;
}

bool CGameObject::isHit()
{
	return false;
}

void CGameObject::Respawn()
{
}

#include "stdafx.h"
#include "Transform.h"
#include "Navigation.h"

#include "Scene.h"

CTransform::CTransform()
	:CComponent()
	, m_tPosition({ 0, 0 })
	, m_nSpeed(0)
{
}

CTransform::~CTransform()
{
}

bool CTransform::InitializeComponent()
{
	return true;
}

bool CTransform::InitializeComponent(vec2 _position, int _speed)
{
	m_tPosition = _position;
	m_nSpeed	= _speed;

	return true;
}

void CTransform::ReleaseComponent()
{
	delete this;
}

void CTransform::MovLeft(CNavigation* _navigation)
{
	vec2	postPosition = { 0,0 };
	int		speed = m_nSpeed;

	while (speed)
	{
		postPosition = m_tPosition;
		postPosition.y -= speed;

		if (_navigation->CheckMove(postPosition))
		{
			m_tPosition.y = postPosition.y;
			break;
		}
		else
			--speed;
	}
}

void CTransform::MovUp(CNavigation* _navigation)
{
	vec2 postPosition = { 0,0 };
	int		speed = m_nSpeed;

	while (speed)
	{
		postPosition = m_tPosition;
		postPosition.x -= speed;

		if (_navigation->CheckMove(postPosition))
		{
			m_tPosition.x = postPosition.x;
			break;
		}
		else
			--speed;
	}
}

void CTransform::MovRight(CNavigation* _navigation)
{
	vec2 postPosition = { 0,0 };
	int		speed = m_nSpeed;

	while (speed)
	{
		postPosition = m_tPosition;
		postPosition.y += speed;

		if (_navigation->CheckMove(postPosition))
		{
			m_tPosition.y = postPosition.y;
			break;
		}
		else
			--speed;
	}
}

void CTransform::MovDown(CNavigation* _navigation)
{
	vec2 postPosition = { 0,0 };
	int		speed = m_nSpeed;

	while (speed)
	{
		postPosition = m_tPosition;
		postPosition.x += speed;

		if (_navigation->CheckMove(postPosition))
		{
			m_tPosition.x = postPosition.x;
			break;
		}
		else
			--speed;
	}
}

CTransform * CTransform::Create(vec2 _position, int _speed)
{
	CTransform* pInstance = new CTransform();
	if (!pInstance->InitializeComponent(_position, _speed))
		SAFE_DELETE(pInstance);

	return pInstance;
}

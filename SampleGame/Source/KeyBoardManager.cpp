#include "stdafx.h"
#include "KeyBoardManager.h"

const unsigned short KEY_LEFT	= 0x0001;
const unsigned short KEY_UP		= 0x0002;
const unsigned short KEY_RIGHT	= 0x0004;
const unsigned short KEY_DOWN	= 0x0008;
const unsigned short KEY_A		= 0x0010;
const unsigned short KEY_S		= 0x0020;
const unsigned short KEY_D		= 0x0040;
const unsigned short KEY_RETURN = 0x0080;
const unsigned short KEY_SPACE	= 0x0100;

IMPLEMENT_SINGLETON(CKeyBoardManager)

CKeyBoardManager::CKeyBoardManager()
{
	Initialize();
}


CKeyBoardManager::~CKeyBoardManager()
{
	Release();
}

bool CKeyBoardManager::Initialize()
{
	m_nKeys = 0;
	m_nPrevKeys = 0;

	return true;
}

int CKeyBoardManager::Update()
{
	m_nKeys = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_nKeys |= KEY_UP;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_nKeys |= KEY_LEFT;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_nKeys |= KEY_DOWN;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_nKeys |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_nKeys |= KEY_RETURN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_nKeys |= KEY_SPACE;

	return NOERROR;
}

void CKeyBoardManager::Release()
{
}


bool CKeyBoardManager::isKeyDown(unsigned short _keycode)
{

	if (!(m_nPrevKeys & _keycode) && (m_nKeys & _keycode))
	{
		m_nPrevKeys |= _keycode;
		return true;
	}

	if ((m_nPrevKeys & _keycode) && !(m_nKeys & _keycode))
	{
		m_nPrevKeys &= ~_keycode;
		return false;
	}

	return false;
}

bool CKeyBoardManager::isKeyUp(unsigned short _keycode)
{
	if (!(m_nPrevKeys & _keycode) && (m_nKeys & _keycode))
	{
		m_nPrevKeys |= _keycode;
		return false;
	}

	if ((m_nPrevKeys & _keycode) && !(m_nKeys & _keycode))
	{
		m_nPrevKeys &= ~_keycode;
		return true;
	}

	return false;
}

#pragma once


class CKeyBoardManager final
{
public:
	CKeyBoardManager();
	~CKeyBoardManager();

	DECLARE_SINGLETON(CKeyBoardManager)

public:
	bool	Initialize();
	int		Update();
	void	Release();
public:
	bool		isKeyPressed(unsigned short _keycode) { return (m_nKeys & _keycode) > 0 ? true : false; }
	bool		isKeyDown(unsigned short _keycode);
	bool		isKeyUp(unsigned short _keycode);
private:
	unsigned short		m_nKeys;
	unsigned short		m_nPrevKeys;
};


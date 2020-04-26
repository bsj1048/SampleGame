#pragma once

class CCell final
{
public:
	enum TILE_AROUND { TILE_LEFT, TILE_UP, TILE_RIGHT, TILE_DOWN, TILE_HERE, TILE_END};
private:
	explicit CCell();
	virtual ~CCell();
public:
	bool	InitializeCell(int _x, int _y);
	void	ReleaseCell();
public:
	vec2	GetIndex() { return vec2(m_nX, m_nY); };
public:
	void	SetBlock(bool _block) { m_bBlock = _block; };
public:
	bool	isBlock() { return m_bBlock; };
public:
	static	CCell* Create(int _x, int _y);
private:
	int		m_nX;
	int		m_nY;
	bool	m_bBlock;
};


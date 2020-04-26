#pragma once

class CObserver;
class CUIManager
{
public:
	CUIManager();
	~CUIManager();

	DECLARE_SINGLETON(CUIManager)

public:
	int		Update();
	void	Render();
private:
	CObserver*		m_pObserver;
};


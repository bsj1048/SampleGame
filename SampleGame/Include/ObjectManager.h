#pragma once

class CGameObject;
class CObjectManager final
{
public:
	CObjectManager();
	~CObjectManager();

	DECLARE_SINGLETON(CObjectManager)

public:
	bool	Initialize();
	int		Update();
	void	Render();
	void	Release();
public:
	const list<CGameObject*>&	GetLayer(const wchar_t* _layerTag) { return m_mapLayers[_layerTag]; };
public:
	bool	AddGameObject(const wchar_t* _layerTag, CGameObject* _object);
private:
	map<const wchar_t*, list<CGameObject*>>				m_mapLayers;
	typedef map<const wchar_t*, list<CGameObject*>>		LAYERMAP;
	typedef list<CGameObject*>	OBJECTLST;
};



#pragma once

class CObserver;
class CSubjectManager
{
public:
	CSubjectManager();
	~CSubjectManager();

	DECLARE_SINGLETON(CSubjectManager)

public:
	bool	Initialize();
	void	Release();
public:
	void*	GetData(const wchar_t* _dataTag) { return m_mapDatas[_dataTag]; };
public:
	void	AddData(const wchar_t* _dataTag, void* _data);
public:
	void	Notify(const wchar_t* _tag);
	void	Subscribe(CObserver* _observer);
	void	UnSubscribe(CObserver* _observer);
private:
	list<CObserver*> m_lstObservers;
	typedef list<CObserver*> OBSERVERLST;

	map<const wchar_t*, void*> m_mapDatas;
	typedef map<const wchar_t*, void*> DATAMAP;
};


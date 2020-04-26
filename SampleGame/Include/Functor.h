#pragma once

#ifndef __FUNCTOR_H__

class CFuntor
{
public:
	explicit CFuntor(const wchar_t* _wstring)
	{
		m_wszString = new  wchar_t[lstrlen(_wstring) + 1];
		lstrcpy(m_wszString, _wstring);
	};
	virtual ~CFuntor()
	{
		SAFE_DELETE(m_wszString);
	};
public:
	template<typename T>
	bool operator()(T& _compare)
	{
		return lstrcmp(m_wszString, _compare.first) == 0 ? true : false;
	}
private:
	wchar_t*	m_wszString;
};

#define __FUNCTOR_H__
#endif // !__FUNCTOR_H__
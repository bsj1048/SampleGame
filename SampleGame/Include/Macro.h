#pragma once

#ifndef __MACRO_H__

#define SAFE_DELETE(ptr) if(ptr) {delete ptr, ptr = nullptr;}
#define SAFE_DELETE_ARRAY(ptr) if(ptr) {delete[] ptr, ptr = nullptr;}

#define NO_COPY(CLASSNAME)								\
private:												\
	CLASSNAME(const CLASSNAME&);						\
	CLASSNAME& operator=(const CLASSNAME&) = default;

#define DECLARE_SINGLETON(CLASSNAME)					\
NO_COPY(CLASSNAME)										\
public:													\
	static	CLASSNAME* GetInstance();					\
	void	DestroyInstance();							\
private:												\
	static  CLASSNAME* m_pInstance;

#define IMPLEMENT_SINGLETON(CLASSNAME)					\
CLASSNAME* CLASSNAME::m_pInstance = nullptr;			\
CLASSNAME* CLASSNAME::GetInstance()						\
{														\
	if (!m_pInstance)									\
		m_pInstance = new CLASSNAME;					\
	return m_pInstance;									\
}														\
void CLASSNAME::DestroyInstance()						\
{														\
	if (m_pInstance)									\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}


#define __MACRO_H__
#endif // !__MACRO_H__

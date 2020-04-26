#include "stdafx.h"
#include "State.h"


CState::CState()
	:m_pHander(nullptr)
{
}


CState::~CState()
{
}

bool CState::InitializeState(void* _arg)
{
	return true;
}

void CState::ReleaseState()
{
	delete this;
}


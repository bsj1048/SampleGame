#include "stdafx.h"
#include "StateHandler.h"
#include "State.h"

CStateHandler::CStateHandler()
{
}


CStateHandler::~CStateHandler()
{
}

bool CStateHandler::InitializeComponent()
{
	m_pCurrentState = nullptr;

	return true;
}

void CStateHandler::ReleaseComponent()
{
	for (auto pair : m_mapStates)
		pair.second->ReleaseState();
	m_mapStates.clear();

	delete this;
}

void CStateHandler::Request()
{
	m_pCurrentState->Excute();
}

bool CStateHandler::AddState(const wchar_t * _stateTag, CState * _state)
{
	auto found = find_if(m_mapStates.begin(), m_mapStates.end(), CFuntor(_stateTag));

	if (found != m_mapStates.end())
		return false;

	m_mapStates.insert(STATEMAP::value_type(_stateTag, _state));

	if(m_mapStates.size() == 1)
		m_pCurrentState = _state;

	_state->SetHandler(this);

	return true;
}

bool CStateHandler::ChangeState(const wchar_t * _stateTag)
{
	auto found = find_if(m_mapStates.begin(), m_mapStates.end(), CFuntor(_stateTag));

	if (found == m_mapStates.end())
		return false;

	if (!m_pCurrentState->Exit())
		return false;
	if (!found->second->Enter())
		return false;

	m_pCurrentState = found->second;

	return true;
}

CStateHandler * CStateHandler::Create()
{
	CStateHandler* pInstance = new CStateHandler();
	if (!pInstance->InitializeComponent())
		SAFE_DELETE(pInstance);

	return pInstance;
}

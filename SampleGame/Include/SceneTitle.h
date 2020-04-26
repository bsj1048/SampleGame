#pragma once

#include "Scene.h"

class CSceneTitle final : public CScene
{
private:
	explicit CSceneTitle();
	virtual ~CSceneTitle();
public:
	// CScene을(를) 통해 상속됨
	virtual bool	InitializeScene()	override;
	virtual int		UpdateScene() override;
	virtual void	RenderScene() override;
	virtual void	ReleaseScene() override;
public:
	static	CSceneTitle* Create();
private:
	// CScene을(를) 통해 상속됨
	virtual void ClearDC() override;
private:
	const wchar_t*	m_wszMessage1 = L"샘플 코드입니다.";
	const wchar_t*	m_wszMessage2 = L"캐릭터를 선택해주세요.";
	const wchar_t*	m_wszMessage3 = L"[1.전사] [2.마법사]";
private:
	int		m_nCurrentMsgNO;
};


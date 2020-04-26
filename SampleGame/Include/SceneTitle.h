#pragma once

#include "Scene.h"

class CSceneTitle final : public CScene
{
private:
	explicit CSceneTitle();
	virtual ~CSceneTitle();
public:
	// CScene��(��) ���� ��ӵ�
	virtual bool	InitializeScene()	override;
	virtual int		UpdateScene() override;
	virtual void	RenderScene() override;
	virtual void	ReleaseScene() override;
public:
	static	CSceneTitle* Create();
private:
	// CScene��(��) ���� ��ӵ�
	virtual void ClearDC() override;
private:
	const wchar_t*	m_wszMessage1 = L"���� �ڵ��Դϴ�.";
	const wchar_t*	m_wszMessage2 = L"ĳ���͸� �������ּ���.";
	const wchar_t*	m_wszMessage3 = L"[1.����] [2.������]";
private:
	int		m_nCurrentMsgNO;
};


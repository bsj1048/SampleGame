#pragma once

#include "GameClass.h"

class CMage final : public CGameClass
{
private:
	explicit CMage();
	virtual ~CMage();
public:
	// CGameClass��(��) ���� ��ӵ�
	virtual bool InitializeClass(void * _arg) override;
	virtual void RenderClass(CTransform * _transform) override;
	virtual void ReleaseClass() override;
public:
	// CGameClass��(��) ���� ��ӵ�
	virtual void GetAttackMsg(wchar_t * _msg) override;
	virtual bool Attack(CTransform * _transform, vec2 _direction) override;
public:
	static	CMage*	Create(void* _arg = nullptr);
};


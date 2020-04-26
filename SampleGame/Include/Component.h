#pragma once


class CComponent abstract
{
protected:
	explicit CComponent();
	virtual ~CComponent();
public:
	virtual bool	InitializeComponent() PURE;
	virtual void	ReleaseComponent() PURE;
};


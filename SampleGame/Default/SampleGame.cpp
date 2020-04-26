// MudGame.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	bool	loop = true;

	CCore*	core = CCore::GetInstance();
	core->Initialize();

	int nFrame = 60;

	while (loop)
	{
		if (nFrame == 0)
		{
			if (core->Update())
				break;
			core->Render();

			nFrame = 60;
		}
		--nFrame;

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			loop = false;
	}

	core->Release();

    return 0;
}


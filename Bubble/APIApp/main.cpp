#include <Windows.h>
#include <GameEngineContents/BubbleCore.h>
#include <GameEngineBase/GameEngineDebug.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//GameEngineDebug::LeakFind(368);
	BubbleCore::GetInst().CoreStart(hInstance);
	
	return 0;
}

/*
멀티바이트 사용 : 프로젝트속성 -> 고급 -> 문자 집합 -> 멀티바이트 사용
wWinMain 사용 : (.exe)프로젝트 속성 -> 링커 -> 시스템 -> 하위 시스템 -> 창
*/
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
��Ƽ����Ʈ ��� : ������Ʈ�Ӽ� -> ��� -> ���� ���� -> ��Ƽ����Ʈ ���
wWinMain ��� : (.exe)������Ʈ �Ӽ� -> ��Ŀ -> �ý��� -> ���� �ý��� -> â
*/
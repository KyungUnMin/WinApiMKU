#pragma once
#include <assert.h>
#include <Windows.h>
#include <string>

// ���� :
class GameEngineDebug
{
public:
	static void LeckCheck();

	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

protected:

private:

	GameEngineDebug();
	~GameEngineDebug();
};


#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);
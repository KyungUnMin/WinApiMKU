#pragma once
#include <Windows.h>
#include <map>
#include <string>

class GameEngineInput
{
public:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool		Down			= false;
		bool		Press			= false;
		bool		Up				= false;
		bool		Free				= true;

		float	PressTime	= 0.0f;
		int		Key				= -1;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(const GameEngineInput&& _Other) noexcept = delete;

	static void Update(float _DeltaTime);
	static void CreateKey(const std::string_view& _Name, int _Key);

	static bool IsKey(const std::string_view& _Name);
	static bool IsDown(const std::string_view& _Name);
	static bool IsUp(const std::string_view& _Name);
	static bool IsPress(const std::string_view& _Name);
	static bool IsFree(const std::string_view& _Name);

	static float GetPressTime(const std::string_view& _Name);


protected:

private:
	GameEngineInput();
	~GameEngineInput();

	static std::map<std::string, GameEngineKey> Keys;
};


#pragma once
#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

class BackGround : public GameEngineActor
{
public:
	static const std::vector<BackGround*>& GetBackGrounds(const std::string_view& _LevelName);

	static BackGround* Find(const std::string_view& _LevelName, size_t _Index);

	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void Reserve(int _Capacity)
	{
		Renders.reserve(_Capacity);
	}

	GameEngineRender* GetRender(size_t _Index);

protected:

private:
	static std::map<std::string, std::vector<BackGround*>> BackGrounds;
	
	std::vector<GameEngineRender*> Renders;


};


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
	BackGround();
	~BackGround();

	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(const BackGround&& _Other) noexcept = delete;

	void RenderReserve(int _Capacity)
	{
		BackGroundRenders.reserve(_Capacity);
	}

	size_t GetRenderSize()
	{
		return BackGroundRenders.size();
	}

	size_t GetRenderCapacity()
	{
		return BackGroundRenders.capacity();
	}

	template <typename RenderOrderEnum>
	GameEngineRender* CreateRender(const std::string_view& _Image, RenderOrderEnum _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);

	GameEngineRender* GetRender(size_t _Index);

protected:

private:
	std::vector<GameEngineRender*> BackGroundRenders;
};


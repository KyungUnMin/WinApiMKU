#pragma once
#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRender;

//내부에 vector<GameEngineRender*>를 들고있는 클래스
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

	//GameEngineRender생성(래핑)
	template <typename RenderOrderEnum>
	GameEngineRender* CreateRender(const std::string_view& _Image, RenderOrderEnum _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	//GameEngineRender생성
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);

	//GameEngineRender 인덱스로 받아오기
	GameEngineRender* GetRender(size_t _Index);

protected:

private:
	std::vector<GameEngineRender*> BackGroundRenders;
};


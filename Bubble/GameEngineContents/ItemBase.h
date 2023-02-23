#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;
class GameEngineRender;

class ItemBase : public GameEngineActor
{
public:
	static const std::string_view NormalImgPath;
	static const float4 CollisionScale;
	static const float4 CollisionOffset;
	static const float4 RenderScale;


	ItemBase();
	virtual ~ItemBase() = 0;

	ItemBase(const ItemBase& _Other) = delete;
	ItemBase(ItemBase&& _Other) noexcept = delete;
	ItemBase& operator=(const ItemBase& _Other) = delete;
	ItemBase& operator=(const ItemBase&& _Other) noexcept = delete;

	void Init(const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) final;
	virtual void Excute() = 0;

	inline GameEngineRender* GetRender()
	{
		return RenderPtr;
	}

private:
	GameEngineCollision*		CollisionPtr		= nullptr;
	GameEngineRender*		RenderPtr		= nullptr;

	void ResourceLoad();
};

#include "NumberRenderObject.h"
#include "GameEngineResources.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineString.h>

NumberRenderObject::NumberRenderObject()
{
}

NumberRenderObject::~NumberRenderObject()
{
}

void NumberRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order)
{
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("숫자 이미지는 무조건 10개로 짤려있어야 합니다.");
	}

	if (0 >= NumberScale.x || 0 >= NumberScale.y)
	{
		MsgAssert("크기가 0으로 숫자를 출력할 수 없습니다.");
	}

	ImageName = _ImageName;
	NumberScale = _Scale;
	Order = _Order;
}

void NumberRenderObject::SetValue(int _Value)
{
	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value);
	GameEngineActor* Actor = GetOwner<GameEngineActor>();

	if (nullptr == Actor)
	{
		MsgAssert("액터만이 NumberRenderObject의 부모가 될수 있습니다.");
	}

	if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
	{
		for (size_t i = 0; i < Numbers.size() - NumberRenders.size(); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}

	float4 RenderPos;

	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		GameEngineRender* Render = NumberRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("숫자랜더러가 nullptr 입니다");
		}

		Render->SetPosition(Pos + RenderPos);
		Render->SetScale(NumberScale);
		Render->SetImage(ImageName);
		Render->SetFrame(Numbers[i]);

		RenderPos.x += NumberScale.x;
	}
}
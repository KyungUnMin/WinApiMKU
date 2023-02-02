#include "BubbleMissle_Normal.h"
#include <GameEngineCore/GameEngineRender.h>

BubbleMissle_Normal::BubbleMissle_Normal()
{

}

BubbleMissle_Normal::~BubbleMissle_Normal()
{

}

void BubbleMissle_Normal::Start()
{
	BubbleMissleBase::Start();

	//�� Ŭ���� ��Ʋ�� ó������ ���ҽ� �ε��ϱ�
	static bool IsLoad = false;
	if (false == IsLoad)
	{
		ResourceLoad("BubbleNormal.bmp", 1, 4);
		IsLoad = true;
	}
}

void BubbleMissle_Normal::CreateAnimation(PlayerCharacterType _CharacterType)
{
	BubbleMissleBase::CreateAnimation(_CharacterType);

	int ThrowAniIndex = static_cast<int>(_CharacterType) * 1;
	GetRender()->CreateAnimation
	({
		.AnimationName = "BubbleIdle",
		.ImageName = "BubbleNormal.bmp",
		.Start = ThrowAniIndex,
		.End = ThrowAniIndex,
		.Loop = false
	});
}

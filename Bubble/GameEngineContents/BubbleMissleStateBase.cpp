#include "BubbleMissleStateBase.h"
#include <GameEngineCore/GameEngineRender.h>
#include "BubbleMissle.h"

BubbleMissleStateBase::BubbleMissleStateBase()
{

}

BubbleMissleStateBase::~BubbleMissleStateBase()
{

}

void BubbleMissleStateBase::EnterState()
{
	GameEngineRender* Render = Bubble->GetRender();
	Render->ChangeAnimation(AniName);
}

#include "Monster_Monsta.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MonsterFSM.h"
#include "MonsterState_ReflectionFly.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"
#include "MonsterState_Falling.h"

const std::string_view		Monster_Monsta::RightImagePath			= "Right_Monsta.bmp";
const std::string_view		Monster_Monsta::LeftImagePath				= "Left_Monsta.bmp";
const std::string_view		Monster_Monsta::RightRageImagePath	= "Right_Monsta_Rage.bmp";
const std::string_view		Monster_Monsta::LeftRageImagePath		= "Left_Monsta_Rage.bmp";
const std::string_view		Monster_Monsta::LockImagePath				= "Monsta_Lock.bmp";
const std::string_view		Monster_Monsta::DeadImagePath				= "Monsta_Dead.bmp";


Monster_Monsta::Monster_Monsta()
{

}

Monster_Monsta::~Monster_Monsta()
{

}



void Monster_Monsta::Start()
{
	MonsterBase::Start();
	ResourceLoad();
	GetRender()->SetPosition(float4::Zero);
	GetCollision()->SetPosition(float4::Zero);

	MonsterState_ReflectionFly* FlyState = GetFSM()->CreateState<MonsterState_ReflectionFly>(MonsterStateType::ReflectionFly);
	FlyState->SetReflectionAngle(ReflectionAngle);
	FlyState->SetRotateRange(MonsterBase::CollisionScale);
	FlyState->SetSpeed(MoveSpeed);

	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	//Falling은 MonsterState의 구조상 넣은 State, Falling으로 들어오면 바로 FlyState 로 변경할 예정
	//(모든 몬스터는 땅을 걸어다닌다는 가정하에 설계된 구조였음)
	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	FallingState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_Monsta::FallingToFly);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::ReflectionFly);
}

void Monster_Monsta::ResourceLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Common");
	Dir.Move("Monster");
	Dir.Move("Monsta");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

void Monster_Monsta::Init(const float4& _StartDir, bool _IsClockWise)
{
	MonsterState_ReflectionFly* FlyState = dynamic_cast<MonsterState_ReflectionFly*>(GetFSM()->GetState(MonsterStateType::ReflectionFly));
	FlyState->SetStartDir(_StartDir);
	FlyState->SetReflectionDir(_IsClockWise);
}

bool Monster_Monsta::FallingToFly(float _DeltaTime)
{
	GetFSM()->ChangeState(MonsterStateType::ReflectionFly);
	return true;
}

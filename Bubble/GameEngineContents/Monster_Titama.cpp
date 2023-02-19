#include "Monster_Titama.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "MonsterFSM.h"
#include "MonsterState_ReflectionFly.h"
#include "MonsterState_Lock.h"
#include "MonsterState_Dead.h"
#include "MonsterState_Falling.h"

const std::string_view		Monster_Titama::RightImagePath				= "Right_Titama.bmp";
const std::string_view		Monster_Titama::LeftImagePath				= "Left_Titama.bmp";
const std::string_view		Monster_Titama::RightRageImagePath		= "Right_Titama_Rage.bmp";
const std::string_view		Monster_Titama::LeftRageImagePath		= "Left_Titama_Rage.bmp";
const std::string_view		Monster_Titama::LockImagePath				= "Titama_Lock.bmp";
const std::string_view		Monster_Titama::DeadImagePath				= "Titama_Dead.bmp";


Monster_Titama::Monster_Titama()
{

}

Monster_Titama::~Monster_Titama()
{

}



void Monster_Titama::Start()
{
	MonsterBase::Start();
	ResourceLoad();
	GetRender()->SetPosition(float4::Zero);
	GetCollision()->SetPosition(float4::Zero);

	MonsterState_ReflectionFly* FlyState = GetFSM()->CreateState<MonsterState_ReflectionFly>(MonsterStateType::ReflectionFly);
	FlyState->SetClockWiseMovePath(true);

	MonsterState_Lock* LockState = GetFSM()->CreateState<MonsterState_Lock>(MonsterStateType::Lock);
	MonsterState_Dead* DeadState = GetFSM()->CreateState<MonsterState_Dead>(MonsterStateType::Dead);

	//Falling은 MonsterState의 구조상 넣은 State, Falling으로 들어오면 바로 FlyState 로 변경할 예정
	//(모든 몬스터는 땅을 걸어다닌다는 가정하에 설계된 구조였음)
	MonsterState_Falling* FallingState = GetFSM()->CreateState<MonsterState_Falling>(MonsterStateType::Falling);
	FallingState->SetStateChangeFunc((StateChangeFuncPtr)&Monster_Titama::FallingToFly);

	for (size_t i = 0; i < AniParams.size(); ++i)
	{
		GetRender()->CreateAnimation(AniParams[i]);
	}

	Start_FSM(MonsterStateType::ReflectionFly);
}

void Monster_Titama::ResourceLoad()
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
	Dir.Move("Titama");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightRageImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftRageImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	IsLoad = true;
}

bool Monster_Titama::FallingToFly(float _DeltaTime)
{
	GetFSM()->ChangeState(MonsterStateType::ReflectionFly);
	return true;
}

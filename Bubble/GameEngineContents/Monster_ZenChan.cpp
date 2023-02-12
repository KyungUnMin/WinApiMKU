#include "Monster_ZenChan.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "MonsterFSM.h"
#include "MonsterStateEnum.h"


#include "ZenChan_Move.h"


const std::string_view Monster_ZenChan::LeftImagePath		= "Left_ZenChan.bmp";
const std::string_view Monster_ZenChan::RightImagePath		= "Right_ZenChan.bmp";
const std::string_view Monster_ZenChan::DeadImagePath		= "ZenChan_Dead.bmp";
const std::string_view Monster_ZenChan::LockImagePath		= "ZenChan_Lock.bmp";



Monster_ZenChan::Monster_ZenChan()
{

}

Monster_ZenChan::~Monster_ZenChan()
{

}

void Monster_ZenChan::Start()
{
	MonsterBase::Start();
	ResourceLoad();

	GetFSM()->CreateState<ZenChan_Move>(MonsterStateType::ZenChan_Move);

	Start_FSM(MonsterStateType::ZenChan_Move);
}



void Monster_ZenChan::ResourceLoad()
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
	Dir.Move("ZenChan");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LeftImagePath))->Cut(4, 8);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(RightImagePath))->Cut(4, 8);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(DeadImagePath))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(LockImagePath))->Cut(3, 2);
	IsLoad = true;
}

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineWindow.h>

void Monster_ZenChan::Render(float _DeltaTime)
{
	float4 Pos = GetPos();
	GameEngineLevel::DebugTextPush("몬스터 위치 :" + std::to_string(Pos.ix()) + "/" + std::to_string(Pos.iy()));

	Rectangle(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(),
		Pos.ix() - 10, Pos.iy() - 10, Pos.ix() + 10, Pos.iy() + 10);
}
#include "OpeningMonster.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "OpeningLevel.h"

//{애니메이션 이름}, {프레임 갯수}, {MonPos 위치값 인덱스}, {애니메이션 인터벌}
const OpeningMonster::MonInfo	OpeningMonster::Info[38] = 
{
	{	"Dorabo",			4,		{0,2},	0.1f		},
	{	"OujiSama",		4,		{0,3},	0.1f		},
	{	"Knightron",	19	,	{0,4},	0.1f		},
	{	"Dranko",			16	,	{0,5},	0.1f		},
	{	"Magician",		21	,	{0,6},	0.1f		},
	{	"DenkyuKun",	3,		{0,7},	0.1f		},
	{	"Ankororin",	4,		{0,8},	0.1f		},

	{	"RoboJ",			3,		{1,1},		0.1f		},
	{	"RocketL",		8,		{1,2},	0.1f		},
	{	"YukiBombo",	4,		{1,3},	0.1f		},
	{	"Mummy",		4,		{1,4},	0.1f		},
	{	"ChuChuMan",	4,		{1,5},	0.1f		},
	{	"JiJiPoppo",		4,		{1,6},	0.15f	},
	{	"KiriKabuKun",	3,		{1,7},	0.15f	},
	{	"BoltMan",		6,		{1,8},	0.1f		},
	{	"StongShell",	4,		{1,9},	0.15f	},

	{	"Monsta",			2,		{2,0},	0.1f		},
	{	"Komso",			4,		{2,1},	0.15f	},
	{	"Kabukky",		4,		{2,2},	0.15f	},
	{	"MyaTa",			4,		{2,3},	0.15f	},
	{	"HeitaKun",		4,		{2,4},	0.15f	},
	{	"Warurin",		6,		{2,5},	0.1f		},
	{	"Hidegons",		8,		{2,6},	0.1f		},
	{	"NoNo",			4,		{2,7},	0.1f		},
	{	"Upper",			2,		{2,8},	0.15f	},
	{	"AmeDama",		8,		{2,9},	0.1f		},
	{	"PuruPuru",		8,		{2,10},	0.05f	},

	{	"Flhoop",			4,		{3,0}	,	0.1f		},
	{	"UniBo",			8,		{3,1}	,	0.1f		},
	{	"Drunk",			4,		{3,2}	,	0.15f	},
	{	"Babebou",		11,	{3,3}	,	0.1f		},
	{	"Invader",		7,		{3,4}	,	0.1f		},
	{	"ZenChan",		11,	{3,5}	,	0.1f		},
	{	"MightA",			8,		{3,6}	,	0.15f	},
	{	"Rappappa",	3,		{3,7}	,	0.2f		},
	{	"CatchMaru",	4,		{3,8}	,	0.15f	},
	{	"RoboL",			3,		{3,9}	,	0.1f		},
	{	"Hattonton",	3,		{3,10},	0.15f	}
};

OpeningMonster::OpeningMonster()
{

}

OpeningMonster::~OpeningMonster()
{

}

void OpeningMonster::Start()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	//기준위치
	const float4 pivot = { 125.f, 225.f };
	//간격
	const float4 nextStep = { 70.f, 100.f };

	//기준 위치를 기준으로 인덱스만큼 이동한 값
	float4 MonPos[4][11];
	for (size_t y = 0; y < 4; ++y)
	{
		for (size_t x = 0; x < 11; ++x)
		{
			MonPos[y][x] = pivot;
			MonPos[y][x] += float4{ nextStep.x * x, nextStep.y * y };
		}
	}

	//애니메이션에 사용되는 시작프레임
	int StartFrame = 0;
	for (size_t i = 0; i < 38; ++i)
	{
		GameEngineRender* Render = CreateRender("Opening_Monster.bmp", OpeningRenderOrder::Monster);

		//이 몬스터에 대한 MonPos값
		const std::pair<int, int>& PosIndex = Info[i].PosIndex;

		//위치 설정
		float4 RenderPos = MonPos[PosIndex.first][PosIndex.second];
		Render->SetPosition(RenderPos);

		//크기 설정
		Render->SetScale({ ScreenSize.x * 0.2f, ScreenSize.y * 0.3f });

		Render->CreateAnimation
		({
			.AnimationName	= Info[i].AniName,
			.ImageName			= "Opening_Monster.bmp",
			.Start					= StartFrame,
			.End						= StartFrame + Info[i].AniIndexCount - 1,
			.InterTimer			= Info[i].AniInterval
		});

		//다음 몬스터의 애니메이션을 위해 시작 프레임 이동
		StartFrame += Info[i].AniIndexCount;

		//애니메이션 실행
		Render->ChangeAnimation(Info[i].AniName);
	}
}
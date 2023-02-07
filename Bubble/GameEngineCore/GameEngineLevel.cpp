#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

bool									GameEngineLevel::IsDebugRender		= false;
float4								GameEngineLevel::TextOutStart		= float4::Zero;
std::vector<std::string>	GameEngineLevel::DeBugTexts;


GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	//생성한 엑터 삭제
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}

	Actors.clear();
}

float4 GameEngineLevel::GetMousePos()
{
	return GameEngineWindow::GetMousePosition();
}

float4 GameEngineLevel::GetMousePosToCamera()
{
	return GameEngineWindow::GetMousePosition() + CameraPos;
}


//엑터가 생성될 때 호출(CreateActor), 엑터의 Start호출
void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}

	_Actor->SetOwner(this);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}


//이 레벨에 존재하는 모든 엑터들을 Order순으로 Update호출
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr == Actor || false == Actor->IsUpdate())
			{
				continue;
			}

			Actor->LiveTime += _DeltaTime;
			Actor->Update(_DeltaTime);
		}
	}

}



void GameEngineLevel::Release()
{
	//콜리전 삭제
	{
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator CollisionStartIter = CollisionList.begin();
			std::list<GameEngineCollision*>::iterator CollisionEndIter = CollisionList.end();

			for (; CollisionStartIter != CollisionEndIter;)
			{
				GameEngineCollision* ReleaseCollision = *CollisionStartIter;

				if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
				{
					++CollisionStartIter;
					continue;
				}

				CollisionStartIter = CollisionList.erase(CollisionStartIter);
			}
		}
	}


	//렌더러 삭제
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			std::list<GameEngineRender*>::iterator RenderStartIter = RenderList.begin();
			std::list<GameEngineRender*>::iterator RenderEndIter = RenderList.end();

			for (; RenderStartIter != RenderEndIter;)
			{
				GameEngineRender* ReleaseRender = *RenderStartIter;

				if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
				{
					++RenderStartIter;
					continue;
				}

				RenderStartIter = RenderList.erase(RenderStartIter);
			}
		}
	}

	//엑터 삭제(엑터 안의 Render와 Collision도 삭제)
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			std::list<GameEngineActor*>::iterator ActorStartIter = ActorList.begin();
			std::list<GameEngineActor*>::iterator ActorEndIter = ActorList.end();

			for (; ActorStartIter != ActorEndIter;)
			{
				GameEngineActor* ReleaseActor = *ActorStartIter;

				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					//Actor의 컴포넌트가 Death상태라면 Delete하기
					ReleaseActor->Release();
					++ActorStartIter;
					continue;
				}

				ActorStartIter = ActorList.erase(ActorStartIter);
				delete ReleaseActor;
				ReleaseActor = nullptr;
			}
		}
	}

}



//이 레벨에 존재하는 모든 엑터들을 Order순으로 Render
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	//GameEngineRender의 Render를 호출
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& ActorList = GroupStartIter->second;

			for (GameEngineRender* Render : ActorList)
			{
				if (nullptr == Render || false == Render->IsUpdate())
					continue;

				Render->Render(_DeltaTime);
			}
		}
	}


	//Actor::Render를 호출
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
					continue;

				Actor->Render(_DeltaTime);
			}
		}
	}

	// 디버그 렌더모드일때 충돌체 크기 보이게 하기
	{
		if (true == IsDebugRender)
		{
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

			for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
			{
				std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;
				std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
				std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

				for (; CollisionIterStart != CollisionIterEnd; ++CollisionIterStart)
				{
					GameEngineCollision* DebugCollision = *CollisionIterStart;
					if (nullptr == DebugCollision || false == DebugCollision->IsUpdate())
					{
						continue;
					}

					DebugCollision->DebugRender();
				}
			}
		}
	}

	//디버그용 텍스트 화면 좌측 상단에 출력
	{
		TextOutStart = float4::Zero;
		
		for (size_t i = 0; i < DeBugTexts.size(); ++i)
		{
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
			TextOutA(ImageDc, TextOutStart.ix(), TextOutStart.iy(), DeBugTexts[i].c_str(), static_cast<int>(DeBugTexts[i].size()));
			TextOutStart.y += 20.0f;
		}

		DeBugTexts.clear();
	}

}



//레벨이 바뀔때 Actor의 LevelChangeEnd를 호출
void GameEngineLevel::ActorLevelChangeEnd(GameEngineLevel* _NextLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

		for (GameEngineActor* Actor : ActorList)
		{
			Actor->LevelChangeEnd(_NextLevel);
		}
	}
}


//레벨이 바뀔때 Actor의 LevelChangeStart를 호출
void GameEngineLevel::ActorLevelChangeStart(GameEngineLevel* _PrevLevel)
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

		for (GameEngineActor* Actor : ActorList)
		{
			Actor->LevelChangeStart(_PrevLevel);
		}
	}
}



//Renders에 GameEngineRender를 등록(GameEngineRender::SetOrder에서 직접 호출)
void GameEngineLevel::PushRender(GameEngineRender* _Render, int _ChangeOrder)
{
	Renders[_Render->GetOrder()].remove(_Render);
	_Render->GameEngineObject::SetOrder(_ChangeOrder);

	if(nullptr == _Render)
	{
		MsgAssert("nullptr인 GameEngineRender를 렌더링 그룹 속에 넣으려고 했습니다");
		return;
	}

	Renders[_Render->GetOrder()].push_back(_Render);
}

void GameEngineLevel::PushCollision(GameEngineCollision* _Collision)
{
	if (nullptr == _Collision)
	{
		MsgAssert("nullptr인 충돌체를 충돌 그룹속에 넣으려고 했습니다.");
	}

	Collisions[_Collision->GetOrder()].push_back(_Collision);
}

#include "BubbleMissle.h"
#include <GameEngineCore/GameEngineLevel.h>

//여기 있는 객체는 Level의 자료구조에 들어가지 않음
BubbleMissle* BubbleMissle::Instance = new BubbleMissle;
std::vector<BubbleMissle*> BubbleMissle::Pool(5, new BubbleMissle);


BubbleMissle::BubbleMissle()
{
	
}

BubbleMissle::~BubbleMissle()
{

}


BubbleMissle* BubbleMissle::Create(int _Order)
{
	//풀에 있는 버블을 다 썼다면
	if (true == Pool.empty())
	{
		//크기 2배로 확장
		Pool.reserve(Pool.capacity() * 2);

		//원래 크기만큼 새로 Bubble 생성
		for (size_t i = 0; i < Pool.capacity() / 2; ++i)
		{
			//이거 아마 Level 설정을 안 해줘서 안 될 것임
			if (nullptr == BubbleMissle::Instance->GetLevel())
			{
				int a = 10;
			}
			
			//생성 및 Level에서 Start 호출시킴
			BubbleMissle::Instance->GetLevel()->CreateActor<BubbleMissle>(_Order);
		}
	}

	//뒤쪽부터 빼내기
	BubbleMissle* Bubble = Pool.back();
	Bubble->On();
	Pool.erase(Pool.end() - 1);

	return Bubble;
}



void BubbleMissle::Start()
{
	//생성 되었을땐 풀에 집에넣고 비활성화
	BubbleMissle::Pool.push_back(this);
	Off();
}



void BubbleMissle::Destroy(BubbleMissle* _Bubble)
{
	//비 활성화 해두고 자료구조에 담아두기
	_Bubble->Off();
	Pool.push_back(_Bubble);
}



void BubbleMissle::Release()
{
	Pool.clear();

	if (nullptr != Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
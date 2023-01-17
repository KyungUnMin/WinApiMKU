#include "BubbleMissle.h"
#include <GameEngineCore/GameEngineLevel.h>

//���� �ִ� ��ü�� Level�� �ڷᱸ���� ���� ����
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
	//Ǯ�� �ִ� ������ �� ��ٸ�
	if (true == Pool.empty())
	{
		//ũ�� 2��� Ȯ��
		Pool.reserve(Pool.capacity() * 2);

		//���� ũ�⸸ŭ ���� Bubble ����
		for (size_t i = 0; i < Pool.capacity() / 2; ++i)
		{
			//�̰� �Ƹ� Level ������ �� ���༭ �� �� ����
			if (nullptr == BubbleMissle::Instance->GetLevel())
			{
				int a = 10;
			}
			
			//���� �� Level���� Start ȣ���Ŵ
			BubbleMissle::Instance->GetLevel()->CreateActor<BubbleMissle>(_Order);
		}
	}

	//���ʺ��� ������
	BubbleMissle* Bubble = Pool.back();
	Bubble->On();
	Pool.erase(Pool.end() - 1);

	return Bubble;
}



void BubbleMissle::Start()
{
	//���� �Ǿ����� Ǯ�� �����ְ� ��Ȱ��ȭ
	BubbleMissle::Pool.push_back(this);
	Off();
}



void BubbleMissle::Destroy(BubbleMissle* _Bubble)
{
	//�� Ȱ��ȭ �صΰ� �ڷᱸ���� ��Ƶα�
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
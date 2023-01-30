#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

//����� ���� �����̴� Actor�� �� Ŭ������ ��ӹ޽��ϴ�
class MovableActor : public GameEngineActor
{
public:
	//������ Obstacle�� �浹ó���� �� �� �ڽ��� �浹 ����(���� Ŭ������ ��������� ���ӽ�ų���� ����)
	static const float ColliderRange;

	static const std::string LeftStr;
	static const std::string RightStr;

	MovableActor();
	virtual ~MovableActor() = 0;

	MovableActor(const MovableActor& _Other) = delete;
	MovableActor(MovableActor&& _Other) noexcept = delete;
	MovableActor& operator=(const MovableActor& _Other) = delete;
	MovableActor& operator=(const MovableActor&& _Other) noexcept = delete;


	//�� ��ü�� ���� �ٶ󺸰� �ִ� ������ string���� ��ȯ
	inline const std::string& GetDirStr()
	{
		return Dir;
	}

	//�� ��ü�� ���� �ٶ󺸰� �ִ� ������ float4(����)�� ��ȯ
	const float4& GetDirVec();

	//�̹� �����ӿ��� �� Ŭ������ ������ �ٲ���� ���ι�ȯ
	inline bool IsDirChanged()
	{
		return DirChanged;
	}


	inline float GetGravityAcc()
	{
		return GravityAcc;
	}

	inline void SetGravityAcc(float _Acc)
	{
		GravityAcc = _Acc;
	}

	inline void SetMoveGravityAcc(float _Acc)
	{
		GravityAcc += _Acc;
	}


protected:
	void Update(float _DeltaTime) override;

private:
	std::string	Dir					= MovableActor::RightStr;
	bool				DirChanged		= false;

	//Y�� ���ӵ�(�߷°� ������ �̿�)
	float			GravityAcc		= 0.0f;

	//�̹� �����ӿ� ������ �ٲ���� üũ
	void CheckDirection();
};


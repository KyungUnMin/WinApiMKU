#pragma once
#include <map>
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"

class ComponentBase;

//����� ���� �����̴� Actor�� �� Ŭ������ ���
class MovableActor : public GameEngineActor
{
public:
	//������ Obstacle�� �浹ó���� �� �� �ڽ��� �浹 ����(���� Ŭ������ ��������� ���ӽ�ų ����)
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


	inline float4 GetAcceleration()
	{
		return Acceleration;
	}

	inline void SetAcceleration(float4 _Acc)
	{
		Acceleration = _Acc;
	}

	inline void SetMoveAcceleration(float4 _Acc)
	{
		Acceleration += _Acc;
	}

	inline void SetGravityAcceleration(float _Y)
	{
		Acceleration.y = _Y;
	}

	void SetDir(const float4& _Dir);


protected:
	//�̹� �����ӿ� ������ �ٲ���� üũ
	virtual void CheckDirection();

private:
	std::string	Dir					= MovableActor::RightStr;
	bool				DirChanged		= false;

	//��ü�� ���ӵ�
	float4			Acceleration	= float4::Zero;

	
};


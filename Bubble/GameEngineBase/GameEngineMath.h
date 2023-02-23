#pragma once
#include <math.h>
#include <cmath>
#include <string>
#include <vector>

class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);

	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 Zero;
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4{ cosf(_Rad), sinf(_Rad), 0.f, 1.f };
	}

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	inline int ix() const
	{
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int iz() const
	{
		return static_cast<int>(z);
	}

	inline int iw() const
	{
		return static_cast<int>(w);
	}

	inline int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	inline int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	inline int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	inline int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}


	void RotationZDeg(float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZRad(float _Rad)
	{
		float4 Copy = *this;
		x = Copy.x * cosf(_Rad) - Copy.y * sinf(_Rad);
		y = Copy.x * sinf(_Rad) + Copy.y * cosf(_Rad);
	}



	//������ ���� ���ϱ�(Degree)
	float GetAngleDeg()
	{
		return GetAngleRad() * GameEngineMath::RadToDeg;
	}

	//������ ���� ���ϱ�(Radian)
	float GetAngleRad()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		//cos(����)�� x���� ���´�
		//�׷� ���Լ��� acos�� x���� ������ ������ ���´�
		float Result = acosf(AngleCheck.x);

		//������ ���ﰢ�Լ��� ���ܻ��Լ�(�ϴ��� ����)�� �ƴϴ�
			//ex) sin(PIE * 1/2) == sin(PIE * 3/2) == 1
			//ex) asin(1) => (PIE * 1/2 ) or (PIE * 3/2) ???
		//�׷��� ���ﰢ�Լ��� ġ���� 0 ~ PIE�� ���ѵȴ�

		//(���� ������ PIE�� �Ѱ��� �ϴ� �������� 
			//���򼱰� ��Ī�Ǵ� ������ ���Ծ��ٸ�)
		if (0.f < AngleCheck.y)
		{
			//������ ���� �������� ��Ī�̵� ��Ų��
			Result = GameEngineMath::PIE2 - Result;
		}

		return Result;
	}


	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size()
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}


	static float4 Lerp(const float4& _Start, const float4& _End, float _Ratio)
	{
		//���͸� �ﰢ������ �����غ��� �� ���� �� �����ϴ��� �� �� �ִ�,(�ﰢ���� ������)
		return _Start * (1.0f - _Ratio) + (_End * _Ratio);
	}

	static float4 LerpClamp(const float4& _Start, const float4& _End, float _Ratio)
	{
		if (_Ratio <= 0.f)
		{
			_Ratio = 0.f;
		}

		if (1.f <= _Ratio)
		{
			_Ratio = 1.f;
		}

		return Lerp(_Start, _End, _Ratio);
	}


	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	float4 operator +(const float4 _Value) const
	{
		float4 Return = float4::Zero;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return {-x, -y, -z, 1.0f};
	}


	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}


	float4 operator*(const float4& _Other) const
	{
		float4 Return;
		Return.x = x * _Other.x;
		Return.y = y * _Other.y;
		Return.z = z * _Other.z;
		return Return;
	}

	bool operator == (const float4& _Other) const
	{
		return (x == _Other.x) && (y == _Other.y) && (z == _Other.z);
	}
	
	bool operator<(const float4& _Other) const
	{
		return (x < _Other.x) && (y < _Other.y) /*&& (z < _Other.z)*/;
	}

	//���� ���� string���� ��ȯ�Ͽ� return
	std::string ToString()
	{
		char ArrReturn[256];
		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);
		return std::string(ArrReturn);
	}
};
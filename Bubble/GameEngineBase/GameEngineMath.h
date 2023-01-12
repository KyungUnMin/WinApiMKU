#pragma once

class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;

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

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	int ix() const
	{
		return static_cast<int>(x); 
	}
	int iy() const
	{
		return static_cast<int>(y); 
	}
	int iz() const
	{
		return static_cast<int>(z); 
	}
	int iw() const
	{
		return static_cast<int>(w); 
	}

	float4 half() const
	{
		return { x * 0.5f, y * 0.5f, z * 0.5f };
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}
	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}
	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}
	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	bool IsZero() const
	{
		return (0.0f == x) && (0.0f == y) && (0.0f == z);
	}

	float4 operator*(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	float4 operator -(const float4& _Other) const
	{
		float4 Return;
		Return.x = x - _Other.x;
		Return.y = y - _Other.y;
		Return.z = z - _Other.z;
		return Return;
	}

	float4& operator+=(const float4 _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}
};

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

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
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
		float4 Return;
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

	float4 operator*(const float4& _Other) const
	{
		float4 Return;
		Return.x = x * _Other.x;
		Return.y = y * _Other.y;
		Return.z = z * _Other.z;
		return Return;
	}
	
};
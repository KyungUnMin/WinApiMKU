#include "GameEngineMath.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;

const float4 float4::Left	   = {-1.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::Right	   = {1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up		   = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Down	   = { 0.0f, 1.0f, 0.0f, 1.0f };

const float4 float4::Forward   = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back	   = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };
#pragma once
#include <string_view>
#include "MonsterBase.h"

class Monster_ZenChan : public MonsterBase
{
public:
	static const std::string_view LeftImagePath;
	static const std::string_view RightImagePath;
	static const std::string_view DeadImagePath;
	static const std::string_view LockImagePath;

	Monster_ZenChan();
	~Monster_ZenChan() override;

	Monster_ZenChan(const Monster_ZenChan& _Other) = delete;
	Monster_ZenChan(Monster_ZenChan&& _Other) noexcept = delete;
	Monster_ZenChan& operator=(const Monster_ZenChan& _Other) = delete;
	Monster_ZenChan& operator=(const Monster_ZenChan&& _Other) noexcept = delete;

	
protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
	void ResourceLoad();
};


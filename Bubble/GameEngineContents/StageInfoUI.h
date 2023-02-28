#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class StageInfoType
{
	AEnter,
	A1,
	A2,
	A3,

	UNKNOWN
};

class RoundLevelBase;
class TextLine;

class StageInfoUI : public GameEngineActor
{
public:
	static std::vector<std::vector<std::string_view>> LevelInfoData;

	StageInfoUI();
	~StageInfoUI() override;

	StageInfoUI(const StageInfoUI& _Other) = delete;
	StageInfoUI(StageInfoUI&& _Other) noexcept = delete;
	StageInfoUI& operator=(const StageInfoUI& _Other) = delete;
	StageInfoUI& operator=(const StageInfoUI&& _Other) noexcept = delete;

	inline void SetInfo(RoundLevelBase* _RoundLevel, StageInfoType _Info)
	{
		RoundLevel = _RoundLevel;
		Info = _Info;
	}
	
	/*
		스테이지 전환될때 On/Off해줘야 함
	*/
	void On() override;
	void Off() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	const float				OffTime			= 3.f;
	float						Timer				= 0.f;
	StageInfoType		Info					= StageInfoType::UNKNOWN;
	RoundLevelBase*	RoundLevel		= nullptr;

	const float4			TextScale			= float4{ 20.f, 30.f };
	TextLine*					Texts[3]			= { nullptr,nullptr, nullptr };

	void SettingTextValue();
};


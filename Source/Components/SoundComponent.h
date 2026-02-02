#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Sound/Sound.h"
#include "Component.h"
#include"../Actors/Actor.h"

struct SoundInfo
{
	bool is3DSound;
	bool followOwner;
	Vector3f position;
	float volumeSound;
	float speedSound;
	bool playLooped;
	bool startPaused;
	bool track;
	E_STREAM_MODE streamMode;
	bool enableSoundEffects;


public:
	SoundInfo(bool _is3DSound = false, Vector3f _position = Vector3f(0.0f, 0.0f, 0.0f), bool _followOwner = false, float _volumeSound = 1.0f, float _speedSound = 1.0f, bool _playLooped = false, bool _startPaused = false, bool _track = false, E_STREAM_MODE _streamMode = E_STREAM_MODE::ESM_AUTO_DETECT, bool _enableSoundEffects = false)
	{
		is3DSound = _is3DSound;
		position = _position;
		followOwner = _followOwner;
		volumeSound = _volumeSound;
		speedSound = _speedSound;
		playLooped = _playLooped;
		startPaused = _startPaused;
		track = _track;
		streamMode = _streamMode;
		enableSoundEffects = _enableSoundEffects;
	}
};

class SoundComponent : public Component
{
	Sound* sound;
	SoundInfo info;
	vector<EffectType> effectsType;

public:
	FORCEINLINE Sound* GetSound() { return sound; }

	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new SoundComponent(_owner, *this);
	}

public:
	SoundComponent(Actor* _owner, const SoundComponent& _other);
	SoundComponent(Actor* _owner, Sound* _sound = nullptr, SoundInfo _info = SoundInfo(), vector<EffectType> _effectsType = vector<EffectType>());
	SoundComponent(Actor* _owner, string _pathSound, SoundInfo _info = SoundInfo(), vector<EffectType> _effectsType = vector<EffectType>());
	~SoundComponent() = default;

public:
	virtual void BeginPlay()  override;
	virtual void Tick(const float _deltatime) override;
	virtual void BeginDestroy() override;

private:
	void InitSound();
	void UpdateSoundPosition();


};


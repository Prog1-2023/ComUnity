//#pragma once
//#include "../Utils/CoreMinimal.h"
//
//enum SoundType
//{
//	MUSIC,
//	EFFECT,
//	UI,
//
//	COUNT_TYPE_SOUND
//};
//
//enum EffectType
//{
//	NO_EFFECT,
//	DISTORTION,
//	ECHO,
//	GARGLE,
//	I3DL2_REVERB,
//	WAWES_REVERB,
//
//
//	COUNT_TYPE_EFFECT
//};
//
//class Sound
//{
//	string id;
//	string pathSound;
//	ISound* sound;
//	ISoundEffectControl* fx;
//	SoundType soundType;
//	//vector<EffectType> effectsType;
//	float soundVolume;
//	float soundSpeed;
//
//
//public:
//
//	FORCEINLINE void SetPause(bool _isPause)
//	{
//		if (sound)
//			sound->setIsPaused(_isPause);
//	}
//	FORCEINLINE void SetSoundVolume(float _volume)
//	{
//		soundVolume = _volume;
//		if (sound)
//			sound->setVolume(soundVolume);
//	}
//	FORCEINLINE void SetSoundSpeed(float _speed)
//	{
//		soundSpeed = _speed;
//		if (sound)
//			sound->setPlaybackSpeed(soundSpeed);
//	}
//	FORCEINLINE void SetSoundPosition(Vector3f _pos)
//	{
//		if (sound)
//		{
//			vec3df _posTemp = vec3df(_pos.x, _pos.y, _pos.z);
//			sound->setPosition(_posTemp);
//		}
//	}
//
//
//	FORCEINLINE ISoundEffectControl* GetEffectControl() { return fx; }
//	FORCEINLINE bool GetIsFinished() { return sound->isFinished(); }
//	FORCEINLINE bool GetPause()
//	{
//		if (sound)
//			return sound->getIsPaused();
//		return false;
//	}
//	FORCEINLINE string GetPathSound() { return pathSound; }
//	FORCEINLINE float GetSoundVolume() { return soundVolume; }
//	FORCEINLINE float GetSoundSpeed() { return soundSpeed; }
//	FORCEINLINE Vector3f GetSoundPosition()
//	{
//		vec3df _pos= sound->getPosition();
//		return Vector3f(_pos.X, _pos.Y, _pos.Z);
//	}
//
//public:
//	Sound(string _pathSound, SoundType _soundType = SoundType::MUSIC, float _soundVolume = 1.0f, float _soundSpeed = 1.0f);
//	~Sound();
//
//public:
//	void Start2DSound(ISoundEngine* _engine, bool _playLooped = false, bool _startPaused = false, bool _track = true, E_STREAM_MODE _streamMode = ESM_AUTO_DETECT, bool _enableSoundEffects = false, vector<EffectType> _effectsType = vector<EffectType>()); // TODO remove enguin and get with manager
//	void Start3DSound(ISoundEngine* _engine, Vector3f _position, bool _playLooped = false, bool _startPaused = false, bool _track = true, E_STREAM_MODE _streamMode = ESM_AUTO_DETECT, bool _enableSoundEffects = false, vector<EffectType> _effectsType = vector<EffectType>()); // TODO remove enguin and get with manager or world, change vec3df to Vector3
//
//	void ApplyEffects(vector<EffectType> _effectsType = vector<EffectType>());
//	void ApplyEffect(EffectType _effectType = EffectType::NO_EFFECT);
//
//	void DisableEffects(vector<EffectType> _effectsType = vector<EffectType>());
//	void DisableEffect(EffectType _effectType = EffectType::NO_EFFECT);
//	void DisableAllEffect();
//
//	/// <summary>
//	/// Start the sound if it is paused
//	/// </summary>
//	void Play();
//
//	/// <summary>
//	/// Stop the sound
//	/// </summary>
//	void Stop();
//
//};
//

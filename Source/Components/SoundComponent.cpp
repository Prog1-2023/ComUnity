//#include "SoundComponent.h"
//#include "../Manager/SoundManager.h"
//
//SoundComponent::SoundComponent(Actor* _owner, const SoundComponent& _other) : Component(_owner)
//{
//	sound = _other.sound;
//	info = _other.info;
//	effectsType = _other.effectsType;
//}
//
//SoundComponent::SoundComponent(Actor* _owner, Sound* _sound, SoundInfo _info, vector<EffectType> _effectsType) : Component(_owner)
//{
//	sound = _sound;
//	info = _info;
//	effectsType = _effectsType;
//}
//
//SoundComponent::SoundComponent(Actor* _owner, string _pathSound, SoundInfo _info, vector<EffectType> _effectsType) : Component(_owner)
//{
//	sound = new Sound(_pathSound);
//	info = _info;
//	effectsType = _effectsType;
//}
//
//void SoundComponent::BeginPlay()
//{
//	SUPER::BeginPlay();
//	InitSound();
//}
//
//void SoundComponent::Tick(const float _deltatime)
//{
//	SUPER::Tick(_deltatime);
//	UpdateSoundPosition();
//}
//
//void SoundComponent::BeginDestroy()
//{
//	SUPER::BeginDestroy();
//
//}
//
//void SoundComponent::InitSound()
//{
//	ISoundEngine* _engine = SoundManager::GetInstance().GetSoundEngine();
//	if (!_engine)
//	{
//		cout << "Error => SoundComponent::InitSound() : ISoundEngine is nullptr" << endl;
//		return;
//	}
//
//	if (info.is3DSound)
//	{
//		sound->Start3DSound(_engine, info.position, info.playLooped, info.startPaused, info.track, info.streamMode, info.enableSoundEffects, effectsType);
//	}
//	else
//	{
//		sound->Start2DSound(_engine, info.playLooped, info.startPaused, info.track, info.streamMode, info.enableSoundEffects, effectsType);
//	}
//
//	if (sound)
//	{
//		sound->SetSoundVolume(info.volumeSound);
//		sound->SetSoundSpeed(info.speedSound);
//	}
//}
//
//void SoundComponent::UpdateSoundPosition()
//{
//	//TODO update Sound Position
//	if (owner)
//	{
//		sound->SetSoundPosition(owner->GetPosition());
//	}
//}

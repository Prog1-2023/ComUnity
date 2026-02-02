//#include "Sound.h"
//#include "../Manager/SoundManager.h"
////#include <string>
//
//Sound::Sound(string _pathSound, SoundType _soundType, float _soundVolume, float _soundSpeed)
//{
//	pathSound = _pathSound;
//	soundType = _soundType;
//	soundVolume = _soundVolume;
//	soundSpeed = _soundSpeed;
//	sound = nullptr;
//	fx = 0;
//
//	id = pathSound + to_string(SoundManager::GetInstance().GetCountSound());
//
//
//	SoundManager::GetInstance().RegisterSound(id, this);
//}
//
//Sound::~Sound()
//{
//	if (sound)
//	{
//		sound->drop();
//	}
//}
//
//void Sound::Start2DSound(ISoundEngine* _engine, bool _playLooped, bool _startPaused, bool _track, E_STREAM_MODE _streamMode, bool _enableSoundEffects, vector<EffectType> _effectsType)
//{
//	sound = _engine->play2D(pathSound.c_str(), _playLooped, _startPaused, _track, _streamMode, _enableSoundEffects);
//	if (sound)
//	{
//		sound->setVolume(soundVolume);
//		sound->setPlaybackSpeed(soundSpeed);
//
//		if (_enableSoundEffects)
//		{
//			if (!fx)
//				fx = sound->getSoundEffectControl();
//			ApplyEffects(_effectsType);
//		}
//
//	}
//}
//
//void Sound::Start3DSound(ISoundEngine* _engine, Vector3f _position, bool _playLooped, bool _startPaused, bool _track, E_STREAM_MODE _streamMode, bool _enableSoundEffects, vector<EffectType> _effectsType)
//{
//	vec3df _positionTemp = vec3df(_position.x, _position.y, _position.z);
//	//sound = SoundManager::GetInstance().GetSoundEngine()->play3D(pathSound.c_str(), _positionTemp, _playLooped, _startPaused, _track, _streamMode, _enableSoundEffects);
//
//	sound = SoundManager::GetInstance().GetSoundEngine()->play3D(pathSound.c_str(), vec3df(0.0f,0.0f,5.0f), _playLooped, true, false, _streamMode, false);
//
//	//SoundManager::GetInstance().GetSoundEngine()->setListenerPosition(vec3df(0.0f, 0.0f, 50.0f), vec3df(0.0f, 0.0f, 0.0f));
//	if (sound)
//	{
//		sound->setIsPaused(false);
//		sound->setVolume(soundVolume);
//		sound->setPlaybackSpeed(soundSpeed);
//
//		if (_enableSoundEffects)
//		{
//			if (!fx)
//				fx = sound->getSoundEffectControl();
//			ApplyEffects(_effectsType);
//		}
//
//	}
//}
//
//void Sound::ApplyEffects(vector<EffectType> _effectsType)
//{
//	int _size = _effectsType.size();
//	for (int _i = 0; _i < _size; _i++)
//	{
//		if (_effectsType[_i] == EffectType::NO_EFFECT) continue;
//		ApplyEffect(_effectsType[_i]);
//	}
//}
//
//void Sound::ApplyEffect(EffectType _effectType)
//{
//	if (!sound)return;
//
//	if (fx)
//	{
//		switch (_effectType)
//		{
//		case DISTORTION:
//			fx->enableDistortionSoundEffect();
//			break;
//		case ECHO:
//			fx->enableEchoSoundEffect();
//			break;
//		case GARGLE:
//			fx->enableGargleSoundEffect();
//			break;
//		case I3DL2_REVERB:
//			fx->enableI3DL2ReverbSoundEffect();
//			break;
//		case WAWES_REVERB:
//			fx->enableWavesReverbSoundEffect();
//			break;
//		default:
//			break;
//		}
//
//		//not hear the difference
//		//fx->enableChorusSoundEffect();		NO
//		//fx->enableCompressorSoundEffect();	NO
//		//fx->enableFlangerSoundEffect();		NO
//		//fx->enableParamEqSoundEffect();		NO
//	}
//}
//
//void Sound::DisableEffects(vector<EffectType> _effectsType)
//{
//	int _size = _effectsType.size();
//	for (int _i = 0; _i < _size; _i++)
//	{
//		if (_effectsType[_i] == EffectType::NO_EFFECT) continue;
//		DisableEffect(_effectsType[_i]);
//	}
//}
//
//void Sound::DisableEffect(EffectType _effectType)
//{
//	if (!sound)return;
//
//	if (fx)
//	{
//		switch (_effectType)
//		{
//		case DISTORTION:
//			fx->disableDistortionSoundEffect();
//			break;
//		case ECHO:
//			fx->disableEchoSoundEffect();
//			break;
//		case GARGLE:
//			fx->disableGargleSoundEffect();
//			break;
//		case I3DL2_REVERB:
//			fx->disableI3DL2ReverbSoundEffect();
//			break;
//		case WAWES_REVERB:
//			fx->disableWavesReverbSoundEffect();
//			break;
//		default:
//			break;
//		}
//
//		//not hear the difference
//		//fx->enableChorusSoundEffect();		NO
//		//fx->enableCompressorSoundEffect();	NO
//		//fx->enableFlangerSoundEffect();		NO
//		//fx->enableParamEqSoundEffect();		NO
//	}
//}
//
//void Sound::DisableAllEffect()
//{
//	if (!fx)
//	{
//		cout << "Error => Sound::DisableAllEffect : fx is not Valid !" << endl;
//		return;
//	}
//	fx->disableAllEffects();
//}
//
//void Sound::Play()
//{
//	if (!sound)
//	{
//		cout << "Error : Can not ask to restart the sound if is never started" << endl;
//		return;
//	}
//	sound->setIsPaused(false);
//}
//
//void Sound::Stop()
//{
//	if (!sound)
//	{
//		cout << "Error : Can not ask to stop the sound if is never started" << endl;
//		return;
//	}
//	sound->setIsPaused(true);
//}
//

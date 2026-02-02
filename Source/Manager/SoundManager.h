#pragma once
#include "../Utils/CoreMinimal.h"
#include "../Sound/Sound.h"
#include "Singleton.h"

class SoundManager : public Singleton<SoundManager>
{
	ISoundEngine* engine;
	map<string, Sound*> allSound;
	int countSound;

public:
	FORCEINLINE int GetCountSound() const { return countSound; }
	FORCEINLINE ISoundEngine* GetSoundEngine() const { return engine; }
	FORCEINLINE void SetListener(Vector3f _position, Vector3f _rotation)
	{ 
		vec3df _posTemp = vec3df(_position.x, _position.y, _position.z);
		vec3df _rotTemp = vec3df(_rotation.x, _rotation.y, _rotation.z);
		engine->setListenerPosition(_posTemp,_rotTemp);
	}

public:
	SoundManager();
	~SoundManager();

public:
	void RegisterSound(string _id, Sound* _sound);
	void UnRegisterSound(string _id);
	bool Exist(string _id);

	void SetPauseAll(bool _isPause);
};


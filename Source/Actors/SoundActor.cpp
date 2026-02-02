#include "SoundActor.h"

SoundActor::SoundActor(Level* _level, string _pathSound, SoundInfo _info, vector<EffectType> _effectsType) : Actor(_level)
{
	sound = nullptr;
	pathSound = _pathSound;
	info = _info;
	effectsType = _effectsType;
}

void SoundActor::Construct()
{
	SUPER::Construct();
	sound = CreateComponent<SoundComponent>(pathSound, info, effectsType);
}

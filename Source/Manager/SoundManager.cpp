//#include "SoundManager.h"
//
//SoundManager::SoundManager()
//{
//	engine = createIrrKlangDevice();
//	if (!engine)
//	{
//		//TODO Assert 
//		cout << "Error => SoundManager::SoundManager : engine is invalid" << endl;
//		return;
//	}
//	allSound = map<string, Sound*>();
//	countSound = 0;
//}
//
//SoundManager::~SoundManager()
//{
//	for (pair<string, Sound*> _value : allSound)
//	{
//		if (_value.second)
//		{
//			//_value.second->Drop();
//			delete _value.second;
//		}
//	}
//	allSound.clear();
//	engine->drop();
//}
//
//void SoundManager::RegisterSound(string _id, Sound* _sound)
//{
//	if (!_sound || Exist(_id)) return;
//	allSound[_id] = _sound;
//	countSound++;
//}
//
//void SoundManager::UnRegisterSound(string _id)
//{
//	if (!Exist(_id)) return;
//	delete allSound[_id];
//	allSound.erase(_id);
//	countSound--;
//}
//
//bool SoundManager::Exist(string _id)
//{
//	for (pair<string, Sound*> _value : allSound)
//	{
//		if (_value.first == _id)
//			return true;
//	}
//	return false;
//}
//
//void SoundManager::SetPauseAll(bool _isPause)
//{
//	for (pair<string, Sound*> _value : allSound)
//	{
//		if (_value.second)
//		{
//			_value.second->SetPause(_isPause);
//		}
//	}
//}

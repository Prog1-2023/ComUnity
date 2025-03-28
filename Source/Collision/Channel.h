//#pragma once
//#include "../Utils/CoreMinimal.h"
//// ReactPhysics3D
////#include <reactphysics3d/reactphysics3d.h>
////#include <reactphysics3d/collision/RaycastInfo.h>
//
////using namespace rp3d;
////using namespace reactphysics3d;
//
//enum Category
//{
//	Category1 = 0x0001,
//	Category2 = 0x0002,
//	Category3 = 0x0003,
//	Category4 = 0x0004,
//	Category5 = 0x0005,
//	Category6 = 0x0006,
//	Category7 = 0x0007,
//	Category8 = 0x0010,
//	Category9 = 0x0011,
//	Category10 = 0x0012,
//	Category11 = 0x0013,
//	Category12 = 0x0014,
//	Category13 = 0x0015,
//	Category14 = 0x0016,
//	Category15 = 0x0017,
//	Category16 = 0x0020,
//	Category17 = 0x0021,
//	Category18 = 0x0022,
//	Category19 = 0x0023,
//	Category20 = 0x0024,
//	Category21 = 0x0025,
//	Category22 = 0x0026,
//	Category23 = 0x0027,
//	Category24 = 0x0030,
//	Category25 = 0x0031,
//	Category26 = 0x0032,
//	Category27 = 0x0033,
//	Category28 = 0x0034,
//	Category29 = 0x0035,
//	Category30 = 0x0037,
//	Category31 = 0x0040,
//	Category32 = 0x0041,
//};
//
////TODO REMOVE TO OTHER CLASS//
////struct RayI 
////{
////	Vector3f startPoint = Vector3f(0,0,0);
////	Vector3f endPoint = Vector3f(0, 0, 0);
////	RAYD::Ray ray = RAYD::Ray(startPoint, endPoint);
////
////	RayI() = default;
////
////	RayI(const Vector3f& _startPoint, const Vector3f& _endPoint)
////	{
////		startPoint = _startPoint;
////		endPoint = _endPoint;
////
////		ray = Ray(startPoint, endPoint);
////	}
////
////	RayI(const Ray& _newRay)
////	{
////		ray = _newRay;
////	}
////};
////TODO REMOVE TO OTHER CLASS//
//
//struct ChannelName
//{
//	string name = "DefaultChannel";
//	bool isDefaultChannel = false;
//
//
//	ChannelName() = default;
//
//	ChannelName(const string& _name, const bool _isDefaultChannel = false)
//	{
//		name = _name;
//		isDefaultChannel = _isDefaultChannel;
//	}
//
//
//	void SetByDefault()
//	{
//		isDefaultChannel = true;
//	}
//};
//static class Channel
//{
//	static map<ChannelName, Category> channelColission;
//	static int index;
//	//TODO REMOVE//
//	//reactphysics3d::RaycastInfo info;
//	//RayI rayI;
//	//TODO REMOVE//
//
//public:
//	static FORCEINLINE map< ChannelName , Category> GetChannelCollision() { return channelColission; }
//
//public:
//	Channel();
//public:
//	static Category GetChannelCollision(const string& _name);
//	static void AddChannelCollision(const ChannelName& _newChannelName);
//	static void RemoveChannelCollision(const ChannelName& _channelName);
//	//static void RemoveChannelCollision(const int _index);
//
//private:
//	void InitChannelCollisionPreset();
//};
//

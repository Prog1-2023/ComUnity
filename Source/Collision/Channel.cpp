//#include "Channel.h"
//Channel::Channel()
//{
//	index = 6;
//	InitChannelCollisionPreset();
//}
//
//
//
//Category Channel::GetChannelCollision(const string& _channel)
//{
//	using It = map<ChannelName, Category>::const_iterator;
//	const It& _start = channelColission.begin();
//	const It& _end = channelColission.end();
//
//	for (It _it = _start; _it != _end; ++_it)
//	{
//		if (_it->first.name == _channel)
//		{
//			return channelColission[_channel];
//		}
//		else
//		{
//			return Category::Category1;
//		}
//	}
//
//
//	//TODO
//	//SetisQueryCollider;
//}
//
//void Channel::AddChannelCollision(const ChannelName& _newChannelName)
//{
//	//value
//	using It = map<ChannelName, Category>::const_iterator;
//	const It& _start = channelColission.begin();
//	const It& _end = channelColission.end();
//
//	for (It _it = _start; _it != _end; ++_it)
//	{
//		if (_newChannelName.name ==  _it->first.name)
//		{
//			return;
//		}
//	}
//	channelColission.emplace(_newChannelName, Category(index) );
//	index++;
//}
//
//void Channel::RemoveChannelCollision(const ChannelName& _channelName)
//{
//	if (_channelName.isDefaultChannel)
//	{
//		cout << "Vous ne pouvez pas supprimez un channel par defaut ! " << endl;
//		return;
//	}
//	channelColission.erase(_channelName);
//}
//
//
//void Channel::InitChannelCollisionPreset()
//{
//	channelColission = map<ChannelName, Category>({
//		{ ChannelName("WorldStatic" , true) ,Category1 },
//		{ ChannelName("WorldDynamic", true) ,Category2 },
//		{ ChannelName("Pawn", true) ,Category3 },
//		{ ChannelName("PhyisicsBody", true) ,Category4 },
//		{ ChannelName("Vehicle", true) ,Category5 },
//		{ ChannelName("Destructible", true) ,Category6 },
//		});
//
//	//Category::
//}

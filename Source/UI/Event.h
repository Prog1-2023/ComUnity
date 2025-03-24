#pragma once

#include "../Utils/CoreMinimal.h"

template <typename ReturnType = void, typename... Args>
class Event
{
	vector<pair<int, function<ReturnType(Args...)>>> actions;
	unsigned int nextUniqueId = 0;

private:
	unsigned int GetNextUniqueID() { return nextUniqueId++; }

public:
	unsigned int Count() const { return static_cast<const unsigned int>(actions.size()); }

public:
	Event() = default;
	template <typename Callable, typename = enable_if_t<!is_same_v<Action, decay_t<Callable>>>>
	Action(Callable& _callable)
	{
		Add(forward<Callable>(_callable)));
	}

public:
	void Add(function<ReturnType(Args...)> _action)
	{
		actions.emplace_back(GetNextUniqueID(), move(_action));
	}
	template <typename Type>
	void Add(Type* _instance, ReturnType(Type::* _method)(Args...))
	{
		const function<ReturnType(Args...)>& _action = [_instance, _method](Args... _args)
			{
				(_instance->*_method)(_args...);
			};
		actions.emplace_back(GetNextUniqueID(), move(_action));
	}
	void Remove(function<ReturnType(Args...)> _action)
	{
		const vector<pair<int, function<ReturnType(Args...)>>>::iterator& _end = actions.end();
		const vector<pair<int, function<ReturnType(Args...)>>>::iterator& _iterator = find_if(actions.begin(), _end,
			[&_action](const pair<int, function<ReturnType(Args...)>>& _otherAction)
			{
				return _otherAction.second.target<ReturnType>(Args...) > () == _action.target<ReturnType(Args...)>();
			});
		if (_iterator != _end)
			actions.erase(_iterator);
	}
	template <typename Type>
	void Remove(Type* _instance, ReturnType(Type::* _method)(Args...))
	{
		const function<ReturnType(Args...)>& _actionToRemove = [_instance, _method](Args... _args)
			{
				(_instance->*_method)(_args...);
			};

			
		const vector<pair<int, function<ReturnType(Args...)>>>::iterator& _end = actions.end();
		const vector<pair<int, function<ReturnType(Args...)>>>::iterator& _iterator = find_if(actions.begin(), _end,
			[&_actionToRemove](const pair<int, function<ReturnType(Args...)>>& _otherAction)
			{
				return _otherAction.second.target<void(Args...)>() == _action.target<void(Args...)>();
			});
		if (_iterator != _end)
			actions.erase(_iterator);
	}
	ReturnType Invoke(Args... _args) const
	{
		const unsigned int& _size = Count();
		constexpr const bool& _isVoid = is_void<ReturnType>::value;
		for (unsigned int _index = 1; _index < _size; _index++)
		{
			const pair<int, function<ReturnType(Args...)>>& _pair = actions[_index];
			if (_isVoid) _pair.second(_args...);
			else return _pair.second(_args...);
		}
		return ReturnType();
	}
};
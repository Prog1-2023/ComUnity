#pragma once
#include "CoreMinimal.h"
#include "../UI/Event.h"

template <typename Type>
class Array
{
	Event<void, Type> onItemAdded;
	Event<void> onCleared;
	Event<void, Type> onItemRemoved;
	std::vector<Type> list;

public:
	// Returns the size of the Array
	const int Size() const { return static_cast<const int>(list.size()); }
	// Returns the vector
	const std::vector<Type>& GetVector() const { return list; }
	// Returns the modifiable vector
	std::vector<Type>& GetVectorReference() { return list; }
	// Called when a new item is added to the Array
	Event<void, Type>& OnItemAdded() { return onItemAdded; }
	// Called when the Array is cleared
	Event<void>& OnCleared() { return onCleared; }
	// Called when an item is removed from the Array
	Event<void, Type>& OnItemRemoved() { return onItemRemoved; }

public:
	Array() = default;
	Array(const std::initializer_list<Type>& _list)
	{
		list = _list;
	}
	Array(const Array<Type>& _otherArray)
	{
		list = _otherArray.list;
	}

public:
	// Adds a new item to the Array
	void Add(const Type& _toAdd)
	{
		list.push_back(_toAdd);
		onItemAdded(_toAdd);
	}
	// Adds the list of elements from another Array
	void Add(const Array<Type>& _otherArray)
	{
		const int& _size = _otherArray.Size();
		for (int _index = 0; _index < _size; _index++)
		{
			const Type& _element = _otherArray[_index];
			Add(_element);
			onItemAdded(_element);
		}
	}
	// Adds the list of elements from a vector
	void Add(const std::vector<Type>& _vector)
	{
		const int& _size = _vector.size();
		for (int _index = 0; _index < _size; _index++)
		{
			const Type& _element = _vector[_index];
			Add(_element);
			onItemAdded(_element);
		}
	}
	// Removes an item from the Array
	const bool Remove(const Type& _toRemove)
	{
		if (!Contains(_toRemove))
			return false;
		const int& _size = Size();
		for (int _index = 0; _index < _size; _index++)
		{
			const Type& _element = list[_index];
			if (_element == _toRemove)
			{
				onItemRemoved(_element);
				list.erase(list.begin() + _index);
				break;
			}
		}
		return true;
	}
	// Display all elements in the Array
	void DisplayAll()
	{
		const int& _size = Size();
		for (int _index = 0; _index < _size; _index++)
		{
			cout << _index << " -> " << list[_index] << endl;
		}
	}
	// Removes an item from the Array at a specific index
	bool RemoveAt(const int& _indexToRemove)
	{
		if (_indexToRemove < 0 || _indexToRemove >= Size())
			return false;
		onItemRemoved(list[_indexToRemove]);
		list.erase(list.begin() + _indexToRemove);
		return true;
	}
	// Removes the first element from the Array
	bool RemoveFirst()
	{
		return RemoveAt(0);
	}
	// Removes the last element from the Array
	bool RemoveLast()
	{
		return RemoveAt(Size() - 1);
	}
	// Checks if the Array is empty
	bool IsEmpty()
	{
		return Size() <= 0;
	}
	// Removes all elements from the Array from index to index
	void RemoveFromToIndexes(const int& _from, const int& _to)
	{
		const int& _size = Size();
		if (_from < 0 || _to < 0 || _from >= _size || _to >= _size)
			return;
		for (int _index = _to; _index >= _from; _index--)
			RemoveAt(_index);
	}
	// Checks if the Array contains an element
	bool Contains(const Type& _toFind)
	{
		return IndexOf(_toFind) != -1;
	}
	// Returns the index of an element in the Array
	int IndexOf(const Type& _toFind)
	{
		const int& _size = Size();
		for (int _index = 0; _index < _size; _index++)
			if (list[_index] == _toFind)
				return _index;
		return -1;
	}
	// Returns the amount of an element in the Array
	int Count(const Type& _toCount)
	{
		const int& _size = Size();
		int _amount = 0;
		for (int _index = 0; _index < _size; _index++)
			if (list[_index] == _toCount)
				_amount++;
		return _amount;
	}
	// Clears the Array
	void Clear()
	{
		list.clear();
		onCleared.Invoke();
	}
	// Delete all elements from the Array then clears it
	void DeleteAll()
	{
		const int& _size = Size();
		for (int _index = 0; _index < _size; _index++)
			CDelete(list[_index]);
		Clear();
	}
	// Returns the first element of the Array
	Type First()
	{
		if (Size() == 0) return Type();
		return list[0];
	}
	// Returns the last element of the Array
	Type Last()
	{
		const int& _size = Size();
		if (_size == 0) return Type();
		return list[_size - 1];
	}
	// Return a copy of the Array with the elements that match the predicate
	Array<Type> Where(Event<bool, Type> _predicate)
	{
		Array<Type> _toReturn;
		for (Type _element : list)
		{
			if (_predicate(_element))
				_toReturn.Add(_element);
		}
		return _toReturn;
	}
	// Return a copy of the Array
	Array<Type> Copy()
	{
		Array<Type> _toReturn;
		for (Type _element : list)
		{
			_toReturn.Add(_element);
		}
		return _toReturn;
	}

public:
	// Returns the reference of an element from the Array at a specific index
	Type& operator[](const int& _index)
	{
		if (_index < 0 || _index >= Size())
			throw std::exception("Index out of bounds!");
		return list[_index];
	}
	// Returns the element from the Array at a specific index
	Type operator[](const int& _index) const
	{
		if (_index < 0 || _index >= Size())
			throw std::exception("Index out of bounds!");
		return list[_index];
	}

public:
	typename std::vector<Type>::iterator begin() { return list.begin(); }
	typename std::vector<Type>::iterator end() { return list.end(); }
	typename std::vector<Type>::const_iterator begin() const { return list.begin(); }
	typename std::vector<Type>::const_iterator end() const { return list.end(); }
};

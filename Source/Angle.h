#pragma once
#include"../Utils/CoreMinimal.h"
struct Angle
{

	
	float degrees;

public :
	Angle()
	{
		degrees = 0;
	}

	
	Angle(float _value,bool isDegrees=true)
	{
		if (isDegrees)
		{
			SetDegrees(_value);
		}
		else
		{
			SetRadians(_value);
		}
	}

	
	Angle(const Angle& _other)
	{
		degrees = _other.degrees;
		
	}
	Angle(Angle&& _other)
	{
		/*x = _other.x;
		y = _other.y;
		_other = Vector3();*/
		*this = move(_other);
	}
	

public:
	FORCEINLINE float GetDegrees()	const 
	{
		return degrees;
	}
	
	FORCEINLINE float GetRadiant()	const 
	{
		return degrees*(M_PI/180.0f);
	}

	FORCEINLINE void SetDegrees(float _degrees)
	{
		degrees = _degrees;
		Normalize();
	}
	FORCEINLINE void SetRadians(float _radians)
	{
		degrees = _radians*(180.0f/M_PI);
		Normalize();
	}


private:
	void Normalize()
	{
		while (degrees < 0)
		{
			degrees += 360;
		}
		while (degrees > 360)
		{
			degrees -= 360;
		}
	}

	//Compute
	Angle& operator = (Angle&& _other)noexcept
	{
		degrees= move(_other.degrees);
		

		return *this;
	}

	Angle& operator = (const Angle& _other)
	{
		return *this = Angle(_other);
	}
	
	Angle operator+(const Angle& _other)const
	{

		return Angle(degrees+_other.degrees);
	}
	Angle operator-(const Angle& _other)const
	{
		return Angle(degrees-_other.degrees);
	}
	Angle operator*(const Angle& _other)const
	{
		return Angle(degrees *_other.degrees);
	}
	Angle operator/(const Angle& _other)const
	{

		return Angle(degrees / _other.degrees);
	}

	//Assignations
	void operator+=(const Angle& _other)
	{
		degrees += _other.degrees;
		
	}
	void operator-=(const Angle& _other)
	{
		degrees -= _other.degrees;
	}
	void operator*=(const Angle& _other)
	{
		degrees *= _other.degrees;
	}
	void operator/=(const Angle& _other)
	{

		degrees /= _other.degrees;
	}

	

	//Comparaison
	bool operator >(const Angle& _other)const noexcept
	{
		return degrees > _other.degrees;
	}
	bool operator >=(const Angle& _other)const noexcept
	{
		return degrees >= _other.degrees;

	}
	bool operator <(const Angle& _other)const noexcept
	{
		return degrees < _other.degrees;

	}
	bool operator <=(const Angle& _other)const noexcept
	{
		return degrees <= _other.degrees;
	}
	bool operator !=(const Angle& _other)const noexcept
	{
		return degrees != _other.degrees;
	}
	bool operator ==(const Angle& _other)const noexcept
	{
		return degrees == _other.degrees;
	}

	//Incrementation
	void operator++()
	{
		++degrees;
		
	}

	void operator--()
	{
		--degrees;
	}
};


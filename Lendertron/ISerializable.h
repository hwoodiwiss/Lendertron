#pragma once
#include <iostream>

class ISerializable
{
public:

	virtual std::ostream& Serialize(std::ostream& os) = 0;
	virtual std::istream& Deserialize(std::istream& is) = 0;

	friend std::ostream& operator <<(std::ostream& os, ISerializable& outObj)
	{
		return outObj.Serialize(os);
	}

	friend std::istream& operator >>(std::istream& is, ISerializable& inObj)
	{
		return inObj.Deserialize(is);
	}

};
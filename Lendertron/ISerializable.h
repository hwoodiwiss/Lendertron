#pragma once
#include <iostream>

//Abstract interface for serializing objects to disk
class ISerializable
{
public:
	//Pure virtual functions that have to be overloaded in derived classes
	virtual std::ostream& Serialize(std::ostream& os) = 0;
	virtual std::istream& Deserialize(std::istream& is) = 0;

	//Out stream operator, allows operator based stream interaction for ISerializabe objects
	friend std::ostream& operator <<(std::ostream& os, ISerializable& outObj)
	{
		//This will call the ISerializable::Serialize as defined in a derived object
		return outObj.Serialize(os);
	}

	//In stream operator, allows operator based stream interaction for ISerializabe objects
	friend std::istream& operator >>(std::istream& is, ISerializable& inObj)
	{
		//This will call the ISerializable::Deserialize as defined in a derived object
		return inObj.Deserialize(is);
	}
	
protected:

	//Helper function for properly reading in a string from istream
	inline std::string InStreamToString(std::istream& in)
	{
		std::streampos prevPos = in.tellg();
		char curr;
		int strCnt = 0;
		do
		{
			strCnt++;
			in.get(curr);
		} while (curr != '\0');
		in.seekg(prevPos);
		char* streamString = new char[strCnt];
		in.read(streamString, strCnt);
		return std::string(streamString);
	}

};
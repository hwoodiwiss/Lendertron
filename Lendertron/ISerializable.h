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
	
protected:
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
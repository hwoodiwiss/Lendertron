#include "User.h"

std::ostream& User::Serialize(std::ostream& outStream)
{
	outStream << m_Username << m_Password << m_AccessLevel;
	return outStream;
}

std::istream& User::Deserialize(std::istream& inStream)
{
	inStream >> m_Username >> m_Password;// >> m_AccessLevel;
	return inStream;
}

std::ostream& operator<<(std::ostream& os, const UserAccessLevel& eAccessLevel)
{
	os << (int)eAccessLevel;
	return os;
}

std::istream& operator>>(std::istream& is, UserAccessLevel& eAccessLevel)
{
	int inVal;
	is >> inVal;
	if (inVal > 0 && inVal <= 2)
	{
		eAccessLevel = static_cast<UserAccessLevel>(inVal);
	}
	else
	{
		eAccessLevel = AL_NONE;
	}
	return is;
}

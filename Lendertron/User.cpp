#include "User.h"

string User::GetAccessLevelString()
{
	string outStr = "None";
	if (m_AccessLevel == AL_USER)
	{
		outStr = "User";
	}
	else if (m_AccessLevel == AL_ADMIN)
	{
		outStr = "Admin";
	}

	return outStr;
}

void User::ChangePassword(string NewPassword, bool firstLogin)
{
	m_Password = NewPassword;
	m_FirstLogin = firstLogin;
}

std::ostream& User::Serialize(std::ostream& outStream)
{
	outStream.write(m_Username.data(), sizeof(char) * m_Username.length() + 1);
	outStream.write(m_Password.data(), sizeof(char) * m_Password.length() + 1);
	outStream.write(reinterpret_cast<char*>(&m_FirstLogin), sizeof(bool));
	outStream.write(reinterpret_cast<char*>(&m_AccessLevel), sizeof(UserAccessLevel));
	return outStream;
}

std::istream& User::Deserialize(std::istream& inStream)
{
	m_Username = InStreamToString(inStream);
	m_Password = InStreamToString(inStream);
	//Very niaive implementation, very platform dependant, should be reviewed in later iterations
	inStream.read(reinterpret_cast<char*>(&m_FirstLogin), sizeof(bool));
	m_AccessLevel = UALFromInStream(inStream);
	return inStream;
}

UserAccessLevel User::UALFromInStream(std::istream& is)
{
	UserAccessLevel eAccessLevel;
	int inVal = 0;
	is.read(reinterpret_cast<char*>(&inVal), sizeof(UserAccessLevel));
	if (inVal > 0 && inVal <= 2)
	{
		eAccessLevel = static_cast<UserAccessLevel>(inVal);
	}
	else
	{
		eAccessLevel = AL_NONE;
	}
	return eAccessLevel;
}

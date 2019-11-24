#pragma once
#include "CommonIncludes.h"
#include "User.h"
#include "ISerializable.h"

enum UserAccessLevel
{
	AL_NONE = 0,
	AL_USER = 1,
	AL_ADMIN = 2
};

class User : public ISerializable
{
public:
	//Default constructor required to be ISerialiazable
	User() : m_AccessLevel(AL_NONE) {}

	string GetUsername() { return m_Username; }
	UserAccessLevel GetAccessLevel() { return m_AccessLevel; };

	std::ostream& Serialize(std::ostream& outStream);
	std::istream& Deserialize(std::istream& inStream);

private:
	UserAccessLevel UALFromInStream(std::istream& is);

	string m_Username;
	string m_Password;
	UserAccessLevel m_AccessLevel;

};
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

class User : ISerializable
{
public:
	//Default constructor required to be ISerialiazable
	User() : m_AccessLevel(AL_NONE) {}

	UserAccessLevel GetAccessLevel() { return m_AccessLevel; };

	std::ostream& Serialize(std::ostream& outStream);
	std::istream& Deserialize(std::istream& inStream);


	//Friend functions for serializing UserAccessLevel
	friend std::ostream& operator<<(std::ostream& os, const UserAccessLevel& eAccessLevel);
	friend std::istream& operator>>(std::istream& is, UserAccessLevel& eAccessLevel);


private:
	string m_Username;
	string m_Password;
	UserAccessLevel m_AccessLevel;

};
#pragma once
#include "Common.h"
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
	//Default constructor required to be ISerialiazable, also default firstlogin to true, if it's not, this can then be overwritten from the datastore
	User() : m_FirstLogin(true), m_AccessLevel(AL_NONE) { }
	User(string Username, string Password, bool FirstLogin, UserAccessLevel AccessLevel) : m_Username(Username), m_Password(Password), m_FirstLogin(FirstLogin), m_AccessLevel(AccessLevel) { }

	//Getters
	string GetUsername() { return m_Username; }
	string GetPassword() { return m_Password; }
	bool IsFirstLogin() { return m_FirstLogin; }
	UserAccessLevel GetAccessLevel() { return m_AccessLevel; };
	string GetAccessLevelString();

	//Modifier functions
	void ChangePassword(string NewPassword, bool firstLogin = false);

	std::ostream& Serialize(std::ostream& outStream);
	std::istream& Deserialize(std::istream& inStream);

private:
	UserAccessLevel UALFromInStream(std::istream& is);

	string m_Username;
	string m_Password;
	bool m_FirstLogin;
	UserAccessLevel m_AccessLevel;

};
#pragma once
#include "CommonIncludes.h"
#include "User.h"

enum UserAccessLevel
{
	AL_NONE = 0,
	AL_USER = 1,
	AL_ADMIN = 2
};

class User
{
public:
	UserAccessLevel GetAccessLevel() { return m_AccesLevel; };
private:
	string m_Username;
	string m_Password;
	UserAccessLevel m_AccesLevel;
};
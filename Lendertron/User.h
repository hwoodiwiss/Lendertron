#pragma once
#include "CommonIncludes.h"

enum UserAccessLevel
{
	AL_USER = 0,
	AL_ADMIN = 1
};

class User
{
public:

private:
	string m_Username;
	string m_Password;
};
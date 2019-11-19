#pragma once
#include <ctime>

class DateTime
{
public:
	DateTime();
	DateTime(long long Seconds);
	static DateTime Now();

private:
	//Seconds since 00:00 Jan 1 1970 UTC
	long long m_Seconds;
};
#include "Utils.h"
#include <random>
#include <time.h>

std::string Utils::GetRandomNumString(int length)
{
	static const char arrNumbers[] = "0123456789";
	std::string output;
	for (int index = 0; index < length; index++)
	{
		srand((unsigned)time(NULL));
		output.push_back(arrNumbers[rand() % (sizeof(arrNumbers) - 1)]);
	}

	return std::string();
}

std::string Utils::GetRandomAlNumString(int length)
{
	return std::string();
}

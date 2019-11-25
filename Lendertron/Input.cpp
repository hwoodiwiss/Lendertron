#include "Input.h"
#include <algorithm>

//Returns a FULL line from stdin. Stream operators will only read up to a space.
string Input::GetUserString()
{
	string sReturn = "";
	getline(cin, sReturn);
	return sReturn;
}

std::string Input::Trim(std::string trimStr)
{
	trimStr.erase(trimStr.begin(), std::find_if(trimStr.begin(), trimStr.end(), [](int curr)->bool { return !std::isspace(curr); }));
	trimStr.erase(std::find_if(trimStr.rbegin(), trimStr.rend(), [](int curr)->bool { return !std::isspace(curr); }).base(), trimStr.end());
	return trimStr;
}

int Input::GetUserInt()
{
	int outputInt = 0;
	bool inRange = false;

	while (!inRange)
	{
		string sInput = GetUserString();

		while (!ValidateIntString(sInput))
		{
			cout << "Please enter a valid number." << endl;
			sInput = GetUserString();
		}

		try
		{
			outputInt = stoi(sInput);
			inRange = true;
		}
		catch (std::out_of_range)
		{
			cout << "Number out of range." << endl;
			cout << "Numbers have to be in the range " << INT_MIN << " - " << INT_MAX << "!" << endl;
			cout << "Please enter a valid number." << endl;
		}
		catch (...)
		{
			cout << "Unknown conversion error occured." << endl;
			cout << "Please enter a valid number." << endl;
		}
	}

	return outputInt;
}

float Input::GetUserFloat()
{
	string sInput = GetUserString();

	while (!ValidateFloatString(sInput))
	{
		cout << "Please enter a valid number.\n";
		sInput = GetUserString();
	}
	
	return stof(sInput);
}

//Notes for validation functions bellow:
//Checks whether characters of the string are within the ascii range for 0 - 9 (48 - 47)
//Also checks for allowable special characters and the strings NULL terminator
//Allowable Characters:
//The first character of a number string is allowed to be '-' (45), to denote a negative number
//In a float, a single instance of '.' (46) is also allowable, as this is the radix point (The point at which you start denoting fractional values)
bool Input::ValidateIntString(string intStr)
{
	if (intStr.length() < 1)
		return false;

	bool bReturn = true;

	for (int index = 0; index < intStr.length(); index++)
	{
		if ((intStr[index] < 48 || intStr[index] > 57) && intStr[index] != 45 && intStr[index] != '\0')
		{
			bReturn = false;
			break;
		}
		else if(intStr[index] == 45 && index != 0)
		{
			bReturn = false;
			break;
		}
	}

	return bReturn;
}

bool Input::ValidateFloatString(string floatStr)
{
	if (floatStr.length() < 1)
		return false;

	bool bReturn = true;
	bool bRadixFound = false;
	for (int index = 0; index < floatStr.length(); index++)
	{

		if ((floatStr[index] < 48 || floatStr[index] > 57) && floatStr[index] != 45 && floatStr[index] != 46 && floatStr[index] != '\0')
		{
			bReturn = false;
			break;
		}
		else if (floatStr[index] == 45 && index != 0)
		{
			bReturn = false;
			break;
		}
		else if (floatStr[index] == 46 && bRadixFound)
		{
			bReturn = false;
			break;
		}

		if (floatStr[index] == 46)
			bRadixFound = true;
	}

	return bReturn;
}

string Input::ToLower(string strValue)
{
	//Transforms the input string to lowercase in place
	std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::tolower);
	return strValue;
}

string Input::ToUpper(string strValue)
{
	//Transforms the input string to uppercase in place
	std::transform(strValue.begin(), strValue.end(), strValue.begin(), ::toupper);
	return strValue;
}
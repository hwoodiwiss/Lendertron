#pragma once
#include "CommonIncludes.h"

class MenuItem
{
public:

private:
	string m_ItemText;
	string m_ItemDescription;
	UserAccessLevel m_RequiredAccessLevel;
};

class Menu
{
public:

private:
	map<int, MenuItem> m_MenuItems;
};
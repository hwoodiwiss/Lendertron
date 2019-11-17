#pragma once
#include "CommonIncludes.h"

class MenuItem
{
public:
	MenuItem(string ItemText, string ItemDescription, UserAccessLevel RequiredAccessLevel) 
		: m_ItemText(ItemText), m_ItemDescription(ItemDescription), m_RequiredAccessLevel(RequiredAccessLevel) {}

	string GetItemText() { return m_ItemText; }
	UserAccessLevel GetRequiredAccessLevel() { return m_RequiredAccessLevel; }
private:
	string m_ItemText;
	string m_ItemDescription;
	UserAccessLevel m_RequiredAccessLevel;
};

class Menu
{
public:
	void AddMenuItem(shared_ptr<MenuItem> pMenuItem);
	void AddMenuItem(string ItemText, string ItemDescription, UserAccessLevel RequiredAccessLevel);

private:
	vector<shared_ptr<MenuItem>> m_MenuItems;
};


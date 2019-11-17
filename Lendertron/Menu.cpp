#include "Menu.h"
#include <sstream>


void Menu::AddMenuItem(shared_ptr<MenuItem> pMenuItem)
{
	m_MenuItems.push_back(pMenuItem);
}

void Menu::AddMenuItem(string ItemText, string ItemDescription, UserAccessLevel RequiredAccessLevel)
{
	m_MenuItems.push_back(std::make_shared<MenuItem>(MenuItem(ItemText, ItemDescription, RequiredAccessLevel)));
}



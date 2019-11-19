#include "MenuManager.h"

MenuManager* MenuManager::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new MenuManager();
	}
	return s_Instance;
}

void MenuManager::AddMenu(string MenuName, Menu* pMenuObj)
{
	m_MenuDictionary.insert(std::pair<string, Menu*>(MenuName, pMenuObj));
}

void MenuManager::SetCurrent(string MenuName)
{
	if (m_MenuDictionary.find(MenuName) != m_MenuDictionary.end())
	{
		m_CurrentMenu = m_MenuDictionary.at(MenuName);
	}
}

Menu* MenuManager::GetCurrent()
{
	return m_CurrentMenu;
}

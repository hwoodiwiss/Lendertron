#pragma once
#include "CommonIncludes.h"
#include "Menu.h"

class MenuManager
{
public:
	static MenuManager* GetInstance();
	void AddMenu(string MenuName, Menu* pMenuObj);
	void SetCurrent(string MenuName);
	Menu* GetCurrent();

private:
	MenuManager() {};

	static MenuManager* s_Instance;
	Menu* m_CurrentMenu;
	map<string, Menu*> m_MenuDictionary;
};
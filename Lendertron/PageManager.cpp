#include "PageManager.h"


void PageManager::AddPage(string MenuName, shared_ptr<Page> pMenuObj)
{
	m_PageDictionary.insert(std::pair<string, shared_ptr<Page>>(MenuName, pMenuObj));
}

shared_ptr<Page> PageManager::GetPage(string PageName)
{
	//Reserve "Exit" for exiting
	if (PageName == "Exit")
	{
		return nullptr;
	}

	if (m_PageDictionary.find(PageName) != m_PageDictionary.end())
	{
		return m_PageDictionary[PageName];
	}

	return nullptr;
}


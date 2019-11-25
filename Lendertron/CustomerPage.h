#pragma once
#include "Page.h"

class CustomerPage : public Page
{
public:
	CustomerPage();
	static shared_ptr<Customer> FindCustomer(shared_ptr<DataManager> appDataManager);
	static shared_ptr<Customer> AddCustomer(shared_ptr<DataManager> appDataManager);

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	void SelectProduct(shared_ptr<DataManager> appDataManager);
	void ChangeCustomer(shared_ptr<DataManager> appDataManager);


	shared_ptr<Customer> m_CurrCustomer;
};
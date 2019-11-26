#pragma once
#include "Page.h"
#include <vector>

//Undefine winapi min macro, as it overrides std::numeric_limits<>::min()
#ifdef min
#undef min()
#endif

//Mmost important page, where the majority of the core functionality is defined
class CustomerPage : public Page
{
public:
	CustomerPage();

	//Static function for finding a customer based on user input
	static shared_ptr<Customer> FindCustomer(shared_ptr<DataManager> appDataManager);

	//Static function for adding a customer based on user input
	static shared_ptr<Customer> AddCustomer(shared_ptr<DataManager> appDataManager);

protected:
	string Execute(string prevPage, shared_ptr<DataManager> appDataManager, shared_ptr<User>& appUser);

private:
	//New loan preocess for the customer in context
	void NewLoan(shared_ptr<DataManager> appDataManager);

	//View existing loans for the current customer
	void ExistingLoans(shared_ptr<DataManager> appDataManager);

	//Change the in-context customer
	void ChangeCustomer(shared_ptr<DataManager> appDataManager);

	//Specific functionality for creating, confirming and storing a loan with links to the user
	bool CreateCustomerLoan(shared_ptr<DataManager> appDataManager, LoanType CustLoanType);

	void PrintLoanTable(std::vector<shared_ptr<Loan>> printLoans);

	shared_ptr<Customer> m_CurrCustomer;
};
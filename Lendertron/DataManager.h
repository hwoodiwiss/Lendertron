#pragma once
#include "CommonIncludes.h"
#include "SerializableVector.h"
#include "ISerializable.h"
#include "Customer.h"
#include "Loan.h"
#include "LoanType.h"
#include "User.h"


class DataManager : public ISerializable
{
public:
	DataManager() {};
	
	User* FindUser(string UserName);

	vector<Customer*> SearchCustomers(string FirstName, string LastName);

	vector<Loan*> GetCustomerLoans(GUID CustomerId);
	Customer* GetLoanCustomer(GUID LoanId);

	void AddCustomer(Customer* pNewCustomerObj);

	std::ostream& Serialize(std::ostream& os);
	std::istream& Deserialize(std::istream& is);

private:
	//Dynamic data loaded from disk
	SerializableVector<Customer> m_Customers;
	SerializableVector<Loan> m_Loans;
	SerializableVector<User> m_Users;

	//Static data 
	vector<LoanType> m_LoanTypes;
};
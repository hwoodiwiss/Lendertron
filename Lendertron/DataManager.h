#pragma once
#include "Common.h"
#include "SerializableVector.h"
#include "ISerializable.h"
#include "Customer.h"
#include "Loan.h"
#include "LoanType.h"
#include "User.h"

namespace fs = std::filesystem;

class DataManager : public ISerializable
{
public:
	DataManager() {};
	//Destructor to clear all loaded data
	~DataManager();
	
	//Persistence methods
	void Save(fs::path filePath);
	void Load(fs::path filePath);

	//Simple Data Getters
	const vector<LoanType>& GetLoanTypes() { return m_LoanTypes; }

	//Data serch functions
	vector<shared_ptr<Customer>> SearchCustomers(string FirstName, string LastName);
	vector<shared_ptr<Loan>> GetCustomerLoans(GUID CustomerId);
	shared_ptr<Customer> GetLoanCustomer(GUID LoanId);
	shared_ptr<User> FindUser(string UserName);
	shared_ptr<Customer> GetCustomer(GUID CustomerId);
	shared_ptr<Loan> GetLoan(GUID LoanId);
	vector<LoanType> GetEligbleLoanTypes(shared_ptr<Customer> pCustomer);

	//Data add functions
	void AddUser(shared_ptr<User> pNewUser);
	void AddCustomer(shared_ptr<Customer> pNewCustomer);
	void AddLoan(shared_ptr<Loan> pNewLoan);
	void AddLoanType(LoanType loanType);

	std::ostream& Serialize(std::ostream& os);
	std::istream& Deserialize(std::istream& is);

private:
	void Update();

	//Dynamic data loaded from disk
	SerializableVector<Customer> m_Customers;
	SerializableVector<Loan> m_Loans;
	SerializableVector<User> m_Users;

	//Static data 
	vector<LoanType> m_LoanTypes;

	fs::path m_UpdatePath;
};
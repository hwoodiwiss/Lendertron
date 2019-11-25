#pragma once
#include "ILoanCriteria.h"

class FinanceCriteria : public ILoanCriteria
{
public:
	FinanceCriteria(double minIncome);
	~FinanceCriteria() {}

	bool Evaluate(shared_ptr<Customer> pCustObj);
private:
	double m_MinIncome;
};
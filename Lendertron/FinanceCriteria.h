#pragma once
#include "ILoanCriteria.h"

class FinanceCriteria : public ILoanCriteria
{
public:
	FinanceCriteria(double minIncome);
	bool Evaluate(Customer* pCustObj);
private:
	double m_MinIncome;
};
#include "FinanceCriteria.h"

FinanceCriteria::FinanceCriteria(double minIncome) : m_MinIncome(minIncome)
{
}

bool FinanceCriteria::Evaluate(Customer* pCustObj)
{
	return pCustObj->GetIncome() >= m_MinIncome;
}

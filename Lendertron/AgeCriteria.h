#pragma once
#include "CommonIncludes.h"
#include "ILoanCriteria.h"


class AgeCriteria : ILoanCriteria
{
public:
	AgeCriteria(byte minAge);
	bool Evaluate(Customer* pCustObj);
private:
	byte m_MinAge;
};

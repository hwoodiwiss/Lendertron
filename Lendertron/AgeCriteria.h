#pragma once
#include "Common.h"
#include "ILoanCriteria.h"


class AgeCriteria : public ILoanCriteria
{
public:
	AgeCriteria(byte minAge);
	~AgeCriteria() {}

	bool Evaluate(shared_ptr<Customer> pCustObj);
private:
	byte m_MinAge;
};

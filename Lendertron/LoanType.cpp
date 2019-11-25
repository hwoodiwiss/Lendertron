#include "LoanType.h"


void LoanType::AddCriteria(shared_ptr<ILoanCriteria> LoanCriteria)
{
	m_Criteria.push_back(LoanCriteria);
}

bool LoanType::IsEligible(shared_ptr<Customer> pCustObj)
{
	if (pCustObj == nullptr)
		return false;
	//Iterates through the critereon for this loan type to determine if the customer is eligible 
	for (auto Critereon : m_Criteria)
	{
		//If any of the Critereon return false, the customer is not eligible
		if (!Critereon->Evaluate(pCustObj))
			return false;
	}

	return true;
}

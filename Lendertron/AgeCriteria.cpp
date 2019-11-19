#include "AgeCriteria.h"

AgeCriteria::AgeCriteria(byte minAge) : m_MinAge(minAge)
{
}

bool AgeCriteria::Evaluate(Customer* customer)
{
	return customer->GetAge() >= m_MinAge;
}

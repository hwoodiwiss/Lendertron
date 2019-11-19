#include "DateTime.h"

DateTime DateTime::Now()
{
	time_t Now = time(0);
	return DateTime(Now);
}

#include "threading/condition_variable.hpp"

namespace threading
{
	condition_variable::condition_variable()
	{
		InitializeConditionVariable(&mInternal);
	}

	void condition_variable::sleep(critical_section& pCriticalSection, unsigned long pTime)
	{
		SleepConditionVariableCS(&mInternal, pCriticalSection.mInternal.get(), pTime);
	}

	void condition_variable::wake()
	{
		WakeConditionVariable(&mInternal);
	}
}

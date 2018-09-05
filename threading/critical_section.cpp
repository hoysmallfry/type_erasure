#include "threading/critical_section.hpp"


namespace threading
{
	critical_section::critical_section() :
	mInternal(new CRITICAL_SECTION())
	{
		InitializeCriticalSection(mInternal.get());

		EnterCriticalSection(mInternal.get());
	}

	critical_section::~critical_section()
	{
		release();
		DeleteCriticalSection(mInternal.get());
	}

	void critical_section::release()
	{
		if(mInternal.get())
			LeaveCriticalSection(mInternal.get());
	}
}

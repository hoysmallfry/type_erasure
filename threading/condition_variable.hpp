#ifndef THREADING_CONDITION_VARIABLE_HPP
#define THREADING_CONDITION_VARIABLE_HPP

#include "threading/critical_section.hpp"

namespace threading
{
	class condition_variable
	{
	public:
		condition_variable();

		void sleep(critical_section& pCriticalSection, unsigned long pTime);
		void wake();

	private :
		CONDITION_VARIABLE mInternal;
	};
}

#endif

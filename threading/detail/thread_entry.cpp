#ifndef THREADING_DETAIL_CREATE_THREAD_HPP
#define THREADING_DETAIL_CREATE_THREAD_HPP

#include "threading/thread.hpp"

#include "threading/detail/thread_info.hpp"

namespace threading
{
	namespace detail
	{ 
		// Here, we simply take the payload, call the function, and wake-up the conditional variable tied.
		
		unsigned long WINAPI thread_entry(void* pArgument)
		{
			auto* ptr = static_cast<thread_info*>(pArgument);	
			thread_info::unique_ptr info(ptr);
			
			info->function();
			info->condition.wake();

			return 0;
		}
	}
}

#endif

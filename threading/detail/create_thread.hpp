#ifndef THREADING_DETAIL_CREATE_THREAD_HPP
#define THREADING_DETAIL_CREATE_THREAD_HPP

#include "threading/thread.hpp"
#include "threading/critical_section.hpp"
#include "threading/detail/thread_info.hpp"
#include "threading/detail/thread_entry.hpp"

namespace threading
{
	namespace detail
	{
		template <typename Func>
		void* create_thread(Func pFunction, creation::type pCreation)
		{
			critical_section critSection;

			// create a thread info type. (This will hold the reference to the external thread entry function)
			thread_info::unique_ptr info(new thread_info(pFunction));

			/*/ 
			The actual thread entry function, the that Win32 calls on, is "thread_entry". It is obscured
			here from the clients that use threading::thread, and the "thread_info" structure is passed in as
			the entry point payload.
			/*/
			thread::handle handle = CreateThread(0, 0, thread_entry, info.get(), std::move(pCreation), 0);

			if (!handle)
				throw std::exception("Could not create thread.");
			
			info->condition.sleep(critSection, INFINITE);
			critSection.release();

			info.release();

			return handle; // handle to thread
		}
	}
}

#endif

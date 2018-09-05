#ifndef THREADING_DETAIL_THREAD_INFO_HPP
#define THREADING_DETAIL_THREAD_INFO_HPP

#include <memory>
#include <functional>

#include "threading/condition_variable.hpp"

// stores information about the thread, including the function that will act as the entry point to the thread

namespace threading
{
	namespace detail
	{
		struct thread_info
		{
			typedef std::unique_ptr<thread_info> unique_ptr;
			typedef std::function<void()> function_type;

			template <typename Func>
			thread_info(Func pFunction) :
			function(pFunction)
			{}

			function_type function;
			condition_variable condition;
		};
	}
}

#endif

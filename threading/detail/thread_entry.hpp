#ifndef THREADING_DETAIL_THREAD_ENTRY_HPP
#define THREADING_DETAIL_THREAD_ENTRY_HPP

namespace threading
{
	namespace detail
	{
		unsigned long WINAPI thread_entry(void* pArgument);
	}
}

#endif

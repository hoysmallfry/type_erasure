#ifndef THREADING_THREAD_HPP
#define THREADING_THREAD_HPP

#include <string>
#include <vector>
#include "windows.hpp"

#include "threading/creation.hpp"
#include "threading/detail/create_thread.hpp"

namespace threading
{
	class thread
	{
	public:
		// We type-define a vector of threads, for convenience
		typedef std::vector<thread*> vector;
		typedef void* handle;

		// The constructor is a template so that we can accept functions that include lambdas
		// Also, notice that I delegate the thread creation to a static function.
		template <typename Func>
		thread(Func pFunction, creation::type pCreation = creation::immmediate) :
		mHandle(detail::create_thread(pFunction, std::move(pCreation)))
		{}

		// We can also specify preexisting raw handle for the thread to take ownership of, if we so chose.
		thread(handle pHandle);
		// We define a rvalue-reference constructor, used in C++11 to take complete ownership of an entity.
		thread(thread&& pMove);

		~thread();

		handle get() const;
		void reset(handle pHandle);
		handle release();

		thread clone();

		void wait(unsigned long pTime = 0);

		void close();

	protected:
		// threads can't be copied.
		thread(const thread& pThread);

		// needs to know its handle.
		handle mHandle;

		/*/
		We define this function as a friend - this was to keep design under Functional or Object-Oriented 
		paradigms, where ever they are best suited. In this case, "wait_all" is best as a stand-alone 
		function, but I did not want to expose "mHeader" publicly to every thing.  
		/*/
		friend void wait_all(const thread::vector& pVector,
			bool pWaitForAll, unsigned long pTime);
	};

	// stand-alone function for waiting on a collection of threads
	template <typename Func>
	void wait_all(const thread::vector& pVector, bool pWaitForAll, unsigned long pTime)
	{
		std::vector<HANDLE> handles;
		for (auto iter = pVector.begin(); iter != pVector.end(); ++iter)
			handles.push_back((*iter)->mHandle);

		//Use the array and pass it to wait for all items.
		WaitForMultipleObjects(handles.size(), handles.data(), pWaitForAll, pTime);
	}

	thread::handle clone(thread::handle pHandle);
}

#endif

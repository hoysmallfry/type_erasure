#include "threading/thread.hpp"

#include "windows.hpp"

namespace threading
{
	thread::thread(handle pHandle) :
	mHandle(pHandle)
	{}

	thread::thread(thread&& pMove) :
	mHandle(pMove.mHandle)
	{
		pMove.mHandle = nullptr;
	}

	thread::~thread()
	{
		close();
	}

	thread::handle thread::get() const
	{
		return mHandle;
	}

	void thread::reset(handle pHandle)
	{
		mHandle = pHandle;
	}

	thread::handle thread::release()
	{
		auto previous = get();
		reset(nullptr);
		return previous;
	}

	void thread::wait(unsigned long pTime)
	{
		// wait for the single handle specified by the name
		WaitForSingleObject(mHandle, pTime);
	}

	thread thread::clone()
	{
		return thread(threading::clone(mHandle));
	}

	void thread::close()
	{
		if (mHandle)
			CloseHandle(mHandle);
	}

	void wait_all(const thread::vector& pVector, bool pWaitForAll, unsigned long pTime)
	{
		std::vector<HANDLE> handles;
		for (auto iter = pVector.begin(); iter != pVector.end(); ++iter)
			handles.push_back((*iter)->mHandle);

		//Use the array and pass it to wait for all items.
		WaitForMultipleObjects(handles.size(), handles.data(), pWaitForAll, pTime);
	}

	thread::handle clone(thread::handle pHandle)
	{
		// get the the parent process
		auto process = GetCurrentProcess();

		// clone the handle with the same permissions, if possible.
		thread::handle result = nullptr;
		DuplicateHandle(process, pHandle, process, &result, 0, true, DUPLICATE_SAME_ACCESS);

		return result;
	}
}

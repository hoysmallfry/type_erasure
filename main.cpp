#include "threading/thread.hpp"

// A template function that simply adds two numbers together
template <typename T>
T add(const T& x, const T& y)
{
	return x + y;
}

int main()
{
	/*/
	Type erasure with lambdas allows for, among other things, intuitively adding a thread that can e
	ssentially take parameters. I chose to do this with the Win32 threading framework specifically to 
	exemplify this as the API does not DIRECTLY allow parameters. Usually, one would have to package 
	references in a structure that takes void pointer, then raw cast the pointer back to the structure type. 
	This is potentially dangerous and should be avoided.

	For what I'm attempting to work, the lambda itself should be designed to take no parameters and return no 
	parameters; This is what I define as a valid thread entry function. However, on the upside, 
	C++ lambdas allow for reference capturing. If the term isn't familiar to you, it simply means that 
	any variables that are alive while within the scope of the lambda definition can be referenced and
	modifed, such as the variable "result".
	/*/

	int result = 0;

	threading::thread t([&]()
			{
				result = add(2, 3);
			});

	t.wait(INFINITE);

	std::cout << result;

	return 0;
}

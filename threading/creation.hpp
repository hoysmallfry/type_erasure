#ifndef THREADING_CREATION_HPP
#define THREADING_CREATION_HPP

#include "windows.hpp"

namespace threading
{
	namespace creation
	{
		enum type
		{
			immmediate = 0,
			suspended = CREATE_SUSPENDED
		};
	}
}

#endif

#ifndef THREADING_CRITICAL_SECTION_HPP
#define THREADING_CRITICAL_SECTION_HPP

#include <memory>
#include "windows.hpp"

namespace threading
{
	class critical_section
	{
	public:
		critical_section();
		~critical_section();

		void release();

	private :
		std::unique_ptr<CRITICAL_SECTION> mInternal;

		friend class condition_variable;
	};
}

#endif

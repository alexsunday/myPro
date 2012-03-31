#include <iostream>
#include <boost/asio.hpp>
#include "COMMON.h"

int main(int argc, char* argv[])
{
	return 
		asio_deadline_timer_async_main(argc, argv);
} 
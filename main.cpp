#include <iostream>
#include "log.hpp"

int main()
{
	INIT_LOGGER();
	LOG_INFO("say something");
	UNINIT_LOGGER();
	return 0;
}

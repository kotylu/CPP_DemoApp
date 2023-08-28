#pragma once

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef DEBUG
	#define LOG_DEBUG(x) std::cout << x << "\n"
#endif // DEBUG


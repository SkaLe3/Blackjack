#pragma once
#include <iostream>
#include <string>


#ifdef BJ_DEBUG
#define BJ_LOG(x) std::cout << "LOG: " << x << "\n";
#else
#define BJ_LOG(x)
#endif
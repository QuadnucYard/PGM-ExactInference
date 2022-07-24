#pragma once
#include <iostream>

void msg(const char* msg) {
	std::cout << msg << std::endl;
}

void msgerr(const char* msg) {
	std::cerr << msg << std::endl;
}
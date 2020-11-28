#ifndef CACHE_TESTS_H
#define CACHE_TESTS_H

#include "LFU.hpp"
#include <iostream>


int runTests();

template <size_t num_elem>
int staticTestBase(uint32_t cache_size, std::array<int, num_elem> elems);

int simpleTest();
int periodicTest();
int linearTest();
int randomTest();


#endif // !CACHE_TESTS_H
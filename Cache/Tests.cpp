#include "Tests.h"
#include <cstdint>
#include <iostream>
#include <array>

int runTests() {
	constexpr uint32_t NUM_TESTS = 3;

	int fails = 0;
	fails += simpleTest();
	fails += periodicTest();
	fails += linearTest();
	//fails += randomTest();
	std::cout << fails << "/" << NUM_TESTS << " test(s) has failed!\n";
	return fails;
}

int simpleTest() {
	constexpr uint32_t NUM_ELEMENTS = 12;
	constexpr uint32_t CACHE_SIZE = 4;
	constexpr std::array<int, NUM_ELEMENTS> IDS = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
	constexpr int MIN_EXPECTED_HITS = 5;

	auto hits = staticTestBase<NUM_ELEMENTS>(CACHE_SIZE, IDS);
	std::cout << "SimpleTest hits: " << hits << "/" << MIN_EXPECTED_HITS << ";\n";
	return hits < MIN_EXPECTED_HITS;
}

int periodicTest() {
	constexpr uint32_t NUM_ELEMENTS = 21;
	constexpr uint32_t CACHE_SIZE = 4;
	constexpr std::array<int, NUM_ELEMENTS> IDS = { 1, 2, 3, 4, 5, 1, 2, 1, 2, 1, 2, 3, 1, 2, 1, 4, 2, 1, 2, 5, 3};
	constexpr int MIN_EXPECTED_HITS = 12;

	auto hits = staticTestBase<NUM_ELEMENTS>(CACHE_SIZE, IDS);
	std::cout << "PeriosicTest hits: " << hits << "/" << MIN_EXPECTED_HITS << ";\n";
	return hits < MIN_EXPECTED_HITS;
} 

int linearTest() {
	constexpr uint32_t NUM_ELEMENTS = 10;
	constexpr uint32_t CACHE_SIZE = 4;
	constexpr std::array<int, NUM_ELEMENTS> IDS = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	constexpr int MIN_EXPECTED_HITS = 0;

	auto hits = staticTestBase<NUM_ELEMENTS>(CACHE_SIZE, IDS);
	std::cout << "LinearTest hits: " << hits << "/" << MIN_EXPECTED_HITS << ";\n";
	return hits < MIN_EXPECTED_HITS;
}

int randomTest() {
	//TODO
	return 0;
}

template <size_t num_elem>
int staticTestBase(uint32_t cache_size, std::array<int, num_elem> elems) {
	cache::LFU<double, int> c(cache_size);

	int hits = 0;
	for (auto i: elems) {
		if (c.lookup(i)) hits += 1;
	}
	return hits;
}

//
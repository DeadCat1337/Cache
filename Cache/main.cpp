#include "LFU.hpp"
#include <iostream>
#include <cstring>
#include "Tests.h"


int main(int argc, char* argv[]) {
	if (argc > 1 && !strcmp(argv[1], "test")) {
		std::cout << "tests:\n";
		runTests();
	}
	else
	{
		size_t m = 0, n = 0, hits = 0;
		std::cin >> m >> n;
		cache::LFU<double, int> c(m);

		for (size_t i = 0; i < n; ++i) {
			page_t p;
			std::cin >> p.id;
			if (c.lookup(p.id)) hits += 1;
		}
		std::cout << hits << "\n";
	}

	return 0;
}

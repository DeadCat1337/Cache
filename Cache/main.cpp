#include "LFU.hpp"

#include <iostream>

struct page_t {
	int id;
	double data; 
};


int main(int argc, char* argv[]) {
	size_t m = 0, n = 0, hits = 0;
	std::cin >> m >> n;
	cache::LFU<double, int> c(m);

	std::cout << "Constructed" << std::endl;

	if (c.full()) {
		std::cout << "Full\r\n";
	}

	for (size_t i = 0; i < n; ++i) {
		page_t p;
		std::cin >> p.id;
		if (c.lookup(p.id)) hits += 1;
	}	
	
	return 0;
}
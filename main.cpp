#include "entrypoint.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
	vsr::EntryPoint entryPoint;

	try {
		entryPoint.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
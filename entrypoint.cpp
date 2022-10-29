#include "entrypoint.hpp"

namespace vsr {
	void EntryPoint::run() {
		while (!VsrWindow.shouldClose()) {
			glfwPollEvents();
		}
	}
}
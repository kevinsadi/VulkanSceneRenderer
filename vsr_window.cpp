#include "vsr_window.hpp"

namespace vsr {
	VsrWindow::VsrWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
		initWindow();
	}

	VsrWindow::~VsrWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void VsrWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
}
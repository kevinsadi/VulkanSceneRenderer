#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace vsr {

	class VsrWindow {

	public:
		VsrWindow(int w, int h, std::string name);
		~VsrWindow();

		// clean up, don't allow duplicate 
		VsrWindow(const VsrWindow&) = delete;
		VsrWindow& operator = (const VsrWindow&) = delete;

		bool shouldClose() {
			return glfwWindowShouldClose(window);
		}

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};


}
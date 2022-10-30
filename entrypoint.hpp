#pragma once

#include "vsr_window.hpp"
#include "vsr_pipeline.hpp"

namespace vsr {
	class EntryPoint {

	public: 
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		VsrWindow VsrWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
		VsrPipeline VsrPipeline{ "simple_shader.vert.spv", "simple_shader.frag.spv" };
	};
}
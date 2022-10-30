#pragma once

#include "vsr_window.hpp"
#include "vsr_pipeline.hpp"
#include "vsr_device.hpp"

namespace vsr {
	class EntryPoint {

	public: 
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		VsrWindow VsrWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
		VsrDevice vsrDevice{ VsrWindow };
		VsrPipeline VsrPipeline{ 
			vsrDevice, 
			"Shaders/simple_shader.vert.spv", 
			"Shaders/simple_shader.frag.spv", 
			VsrPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)
		};
	};
}
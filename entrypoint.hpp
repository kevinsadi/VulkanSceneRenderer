#pragma once

#include "vsr_window.hpp"
#include "vsr_pipeline.hpp"
#include "vsr_device.hpp"
#include "vsr_swap_chain.hpp"

// std
#include <memory>
#include <vector>


namespace vsr {
	class EntryPoint {

	public: 
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		EntryPoint();
		~EntryPoint();

		// Delete copy constructors (smart pointer witchcraft)
		EntryPoint(const EntryPoint&) = delete;
		EntryPoint&operator = (const EntryPoint&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		VsrWindow vsrWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
		VsrDevice vsrDevice{ vsrWindow };
		VsrSwapChain vsrSwapChain{ vsrDevice, vsrWindow.getExtent() };
		std::unique_ptr<VsrPipeline> vsrPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}
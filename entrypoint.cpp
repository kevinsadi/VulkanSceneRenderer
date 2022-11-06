#include "entrypoint.hpp"

// std
#include <stdexcept>

namespace vsr {
	EntryPoint::EntryPoint() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	EntryPoint::~EntryPoint() {
		vkDestroyPipelineLayout(vsrDevice.device(), pipelineLayout, nullptr);
	}


	void EntryPoint::run() {
		while (!vsrWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

	void EntryPoint::createPipelineLayout() {
		// default empty pipeline layout
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		if (vkCreatePipelineLayout(vsrDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout");
		}
	}

	void EntryPoint::createPipeline() {
		// auto is good to use when we easily infer the type from the right or the data type is monstorous
		PipelineConfigInfo pipelineConfig{};
		VsrPipeline::defaultPipelineConfigInfo(
			pipelineConfig,
			vsrSwapChain.width(),
			vsrSwapChain.height()
		);
		// right now, we're building out our render pass with our pipeline, REMEMBER TO MOVE THIS LATER
		pipelineConfig.renderPass = vsrSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		vsrPipeline = std::make_unique<VsrPipeline>(
			vsrDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig
			);
	}

	// to be implemented soon
	void EntryPoint::createCommandBuffers() {}

	// to be implemented soon
	void EntryPoint::drawFrame() {}
}
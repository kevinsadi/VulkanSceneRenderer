#include "entrypoint.hpp"

// std
#include <stdexcept>
#include <array>

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
			drawFrame();
		}

		vkDeviceWaitIdle(vsrDevice.device());
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

	void EntryPoint::createCommandBuffers() {
		commandBuffers.resize(vsrSwapChain.imageCount());

		// Buffers are created and destroyed often, this allows us to do this operation quickly by memory management
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = vsrDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(vsrDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers");
		}

		for (int i = 0; i < commandBuffers.size(); i++) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffer");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = vsrSwapChain.getRenderPass();
			renderPassInfo.framebuffer = vsrSwapChain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = vsrSwapChain.getSwapChainExtent();

			// array over a vector here because we only have 2 clearValues ever
			std::array<VkClearValue, 2> clearValues{};
			// attachment decisions made in render pass
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f }; // attachment one of frame buffer is color
			clearValues[1].depthStencil = { 0.1f, 0 }; // attachment two of frame buffer is depth
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE); // not using secondary command buffers rn
			vsrPipeline->bind(commandBuffers[i]);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to record command buffer");
			}
		}
	}

	// to be implemented soon
	void EntryPoint::drawFrame() {
		uint32_t imageIndex;
		// result determines if process of swapping chain buffers worked 
		auto result = vsrSwapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image");
		}
		result = vsrSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to show image from swap chain");
		}
	}
}
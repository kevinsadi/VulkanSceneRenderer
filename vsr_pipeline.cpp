#include "vsr_pipeline.hpp"

// std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace vsr {
	VsrPipeline::VsrPipeline(
		VsrDevice& device,
		const std::string& vertFilepath,
		const std::string& fragFilePath,
		const PipelineConfigInfo& configInfo) : vsrDevice{device} {
		
		createGraphicsPipeline(vertFilepath, fragFilePath, configInfo);
	}

	std::vector<char> VsrPipeline::readFile(const std::string& filepath) {
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary};
		
		if (!file.is_open()) {
			throw std::runtime_error("failed to open file " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void VsrPipeline::createGraphicsPipeline(
		const std::string& vertFilePath, 
		const std::string& fragFilePath, 
		const PipelineConfigInfo& configInfo) {
		
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		std::cout << "vertex shader file size is " << vertCode.size();
		std::cout << "fragment shader file size is " << fragCode.size();

	}

	void VsrPipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(vsrDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
			throw std::runtime_error("failed to create shader module");
		}
	}

	PipelineConfigInfo VsrPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
		PipelineConfigInfo configInfo{};
		return configInfo;
	}



}
#pragma once

#include "vsr_device.hpp"

// std
#include <string>
#include <vector>

namespace vsr {

	struct PipelineConfigInfo {};

	class VsrPipeline {

	public:
		VsrPipeline(
			VsrDevice& device, 
			const std::string& vertFilepath, 
			const std::string& fragFilePath, 
			const PipelineConfigInfo& configInfo);
		~VsrPipeline() {}

		VsrPipeline(const VsrPipeline&) = delete;
		void operator = (const VsrPipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);


	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
			const std::string& vertFilePath, 
			const std::string& fragFilePath,
			const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		VsrDevice& vsrDevice; // DANGEROUS, because this member variable can be a hanging reference if it outlives it's object it references
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};

}
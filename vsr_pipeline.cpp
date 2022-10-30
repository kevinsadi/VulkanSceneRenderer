#include "vsr_pipeline.hpp"

// std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace vsr {
	VsrPipeline::VsrPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
		createGraphicsPipeline(vertFilepath, fragFilepath);
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

	void VsrPipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath) {
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		std::cout << "vertex shader file size is " << vertCode.size();
		std::cout << "fragment shader file size is " << fragCode.size();

	}

}
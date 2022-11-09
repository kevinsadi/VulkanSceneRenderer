# VulkanSceneRenderer
Vulkan Scene Renderer is my own toy graphics pipeline / scene renderer. The end goal of this project is a fully actualized game engine that is primarily focused on rendering scenes. I've always loved beautiful environments, but I've come to find recently that I love beautiful visualizations even more. This project serves to not only help me understand graphics more in depth, but also allow me to create a platform to create visualizations to geometrically build intuition towards 3D math. 

The renderer can currently render triangle geometry directly specified in it's vertex shader. It is configured for all GPUs, with backface-cullling and triple buffering to render frames. 

Currently, it is capable of rendering 2D geometry, but I hope to continutally update it with new features including:
1) Loading 3d models
2) Perspective and Orthographic Projections
3) Lighting and shadows
4) Post processing

## Setup

Follow setup for your platform referencing [Vulkan Tutorial](https://vulkan-tutorial.com/Development_environment#page_Windows)

## Directory Structure

main.cpp - runs the renderer, handles top level errors

entrypoint.cpp - handles initializing pipeline and necessary objects for rendering. Includes: the window with GLFM, configuring the Vulkan device, configuring swap chain, building graphics pipeline (input assembly, vertex shader, rasterization, fragment shading, and output), and initializing the command buffer. 

vsr_window.cpp - Creates window using GLFW

vsr_pipeline.cpp - Creates graphics pipeline, creates shader modules from compiled GLSL, and specifying pipeline parameters (viewport info, scissor info, rasterization info, multisample info, color blend info, depth buffer info).

vsr_swapchain.cpp - configure swap chain for outputting images to and handling swapping between drawing to framebuffers and reading from framebuffers. Configures VSync, color buffer attachment, and depth buffer attachment). Currently uses mailbox present mode so the GPU never idles. 

vsr_device.cpp - build Vulkan device. Handles create a Vulkan app instance, creating a debug messenger, creating a window surface, picking the physical device (ensuring GPU is compatiable with Vulkan / configuring triple chain buffer / 

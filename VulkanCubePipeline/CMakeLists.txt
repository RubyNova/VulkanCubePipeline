# CMakeList.txt : CMake project for VulkanCubePipeline, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

# Add source to this project's executable.
add_executable (VulkanCubePipeline "VulkanCubePipeline.cpp" "VulkanCubePipeline.h" "src/VulkanPipelineService.cpp" "include/VulkanPipelineService.h" "include/QueueFamilyIndices.h" "include/SwapChainSupportDetails.h" "include/FileLoadingService.h")
target_link_libraries(VulkanCubePipeline Vulkan::Vulkan glfw glm)

# TODO: Add tests and install targets if needed.

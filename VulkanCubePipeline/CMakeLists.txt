# CMakeList.txt : CMake project for VulkanCubePipeline, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

find_path(STB_INCLUDES stb_image.h include)



# Add source to this project's executable.
add_executable (VulkanCubePipeline "VulkanCubePipeline.cpp" "VulkanCubePipeline.h" "src/VulkanPipelineService.cpp" "include/VulkanPipelineService.h" "include/QueueFamilyIndices.h" "include/SwapChainSupportDetails.h" "include/FileLoadingService.h" "include/Vertex.h" "include/CameraBufferObject.h" "src/VulkanTools.cpp" "include/VulkanTools.h" "include/VulkanInitializers.hpp")
target_include_directories(VulkanCubePipeline PRIVATE ${STB_INCLUDES})

target_link_libraries(VulkanCubePipeline Vulkan::Vulkan glfw glm jsoncpp_lib)

# Library target
add_library (MiniRenderVulkanPipeline "src/VulkanPipelineService.cpp" "include/VulkanPipelineService.h" "include/QueueFamilyIndices.h" "include/SwapChainSupportDetails.h" "include/FileLoadingService.h" "include/Vertex.h" "include/CameraBufferObject.h" "src/VulkanTools.cpp" "include/VulkanTools.h" "include/VulkanInitializers.hpp")
target_include_directories(MiniRenderVulkanPipeline PRIVATE ${STB_INCLUDES})

target_link_libraries(MiniRenderVulkanPipeline Vulkan::Vulkan glfw glm jsoncpp_lib)

# TODO: Add tests and install targets if needed.

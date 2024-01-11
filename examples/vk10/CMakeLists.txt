find_package(Vulkan REQUIRED)

add_library(vkb STATIC 3rd_party/vk-bootstrap/VkBootstrap.cpp)
target_include_directories(vkb PUBLIC 3rd_party/vk-bootstrap ${Vulkan_INCLUDE_DIR})

add_executable(vk10 main.cpp)
target_link_libraries(vk10 PRIVATE RGFW vkb Vulkan::Vulkan)

add_custom_command(
        TARGET vk10 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different  ${CMAKE_CURRENT_SOURCE_DIR}/shaders "${CMAKE_CURRENT_BINARY_DIR}/"
        DEPENDS ${OZZ_DATA_FILE}
        VERBATIM
)

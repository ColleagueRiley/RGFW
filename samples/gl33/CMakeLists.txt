add_library(simple-opengl-loader INTERFACE)
target_include_directories(simple-opengl-loader INTERFACE 3rd_party/simple-opengl-loader)

add_executable(gl33 main.cpp)
target_link_libraries(gl33 PRIVATE RGFW simple-opengl-loader)

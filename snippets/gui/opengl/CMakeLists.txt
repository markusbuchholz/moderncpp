find_package(OpenGL)
if (NOT OPENGL_FOUND)
    return()
endif()

if (NOT TARGET glad)
    CPMAddPackage(NAME glad GIT_REPOSITORY https://github.com/Dav1dde/glad GIT_TAG df8e9e16110b305479a875399cee13daa0ccadd9 VERSION 0.1.33)
endif()

if (NOT TARGET glfw)
CPMAddPackage(NAME glfw GIT_REPOSITORY https://github.com/glfw/glfw VERSION 3.3.2 GIT_TAG 3.3.2 OPTIONS "GLFW_BUILD_DOCS OFF" "GLFW_BUILD_EXAMPLES OFF" "GLFW_BUILD_TESTS OFF" "GLFW_INSTALL OFF")
endif()

add_executable(opengl_hello opengl_hello.cpp)
target_link_libraries(opengl_hello PUBLIC glad glfw)
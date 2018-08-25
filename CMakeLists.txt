cmake_minimum_required(VERSION 3.1)

project(LearningGLES2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(OpenGLES2 REQUIRED)
find_package(LibEpoxy REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
    "${CMAKE_SOURCE_DIR}"
    ${OPENGLES2_INCLUDE_DIRS}
    ${LIBEPOXY_INCLUDE_DIRS}
)

link_libraries(
    ${OPENGLES2_LIBRARIES}
    ${LIBEPOXY_LIBRARIES}
    glfw
)

add_definitions(${OPENGLES2_DEFINITIONS})

add_executable(triangle
    GLES2Application.cpp
    TriangleApplication.cpp
    main.cpp
)
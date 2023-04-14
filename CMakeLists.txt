cmake_minimum_required(VERSION 3.0.0)
project(assimp-test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(assimp-test main.cpp source/Model.cpp)

include_directories(third-party/include/ include/ $ENV{VULKAN_SDK}/Include)

target_link_libraries(assimp-test ${PROJECT_SOURCE_DIR}/third-party/lib/assimp-vc143-mt.lib)

target_compile_features(assimp-test PRIVATE cxx_std_17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

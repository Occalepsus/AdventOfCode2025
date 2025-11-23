# CMakeList.txt: CMake project for AdventOfCode2025, include sources and define
# project-specific logic here.
#
cmake_minimum_required(VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("AdventOfCode2025")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Add source files to the executable for this project.
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})

# Organize files in IDEs
source_group("Header" FILES ${HEADER_FILES})
source_group("Source" FILES ${SRC_FILES})

# Include the header files directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Set the output directory for the compiled binary
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Generated/build"
)

# Set C++20 standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# Find and link CURL library
find_package(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)

# Group predefined targets in IDEs that support it
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(PREDEFINED_TARGETS_FOLDER "CustomTargets")
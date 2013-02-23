cmake_minimum_required(VERSION 2.6)
project(rock-n-roll-soul)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB HEADER_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB INLINE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.inl")

file(GLOB SRCFILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")

set(EXECUTABLE_NAME "rock-n-roll-soul")
add_executable(rock-n-roll-soul ${SRCFILES} ${HEADER_FILES} ${INLINE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

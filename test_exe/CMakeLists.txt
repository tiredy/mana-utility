cmake_minimum_required(VERSION 3.2...3.3)

project("TestExecutable" LANGUAGES "CXX" VERSION "1.0")

set(EXECUTABLE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
set(EXECUTABLE_LINK_LIBS "${EXECUTABLE_LINK_LIBS}" "${CMAKE_DL_LIBS} -lpthread")

add_executable(TestExecutable "${EXECUTABLE_SRC}")
target_link_libraries(TestExecutable PRIVATE "${EXECUTABLE_LINK_LIBS}")
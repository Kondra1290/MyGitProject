cmake_minimum_required(VERSION 3.0)
project(GuessNumber)

find_package(Gettext REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(guess src/guess.c)

target_link_libraries(guess ${GETTEXT_LIBRARIES})

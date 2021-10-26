cmake_minimum_required(VERSION 3.16)
project(my_deque)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(my_deque main.cpp Deque.h)

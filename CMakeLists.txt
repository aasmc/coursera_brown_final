cmake_minimum_required(VERSION 3.19)
project(coursera_brown_final)

set(CMAKE_CXX_STANDARD 17)
set(APP_DOMAIN ./)
set(APP_PART_A part_a_b)


include_directories(${APP_DOMAIN})
include_directories(${APP_PART_A})


add_executable(coursera_brown_final part_a_b/main.cpp iterator_range.h profile.h test_runner.h test_runner.cpp part_a_b/stop.h part_a_b/stop.cpp part_a_b/bus.h part_a_b/bus.cpp part_a_b/station_manager.h part_a_b/station_manager.cpp part_a_b/request_manager.h part_a_b/utils.h part_a_b/utils.cpp part_a_b/request_manager.cpp)
cmake_minimum_required(VERSION 3.19)
project(coursera_brown_final)

set(CMAKE_CXX_STANDARD 17)
set(APP_DOMAIN ./)
set(APP_PART_A part_a_b_c)
set(APP_PART_C part_c)


include_directories(${APP_DOMAIN})
include_directories(${APP_PART_A})
include_directories(${APP_PART_C})


add_executable(coursera_brown_final part_a_b_c/main.cpp iterator_range.h profile.h test_runner.h test_runner.cpp part_a_b_c/stop.h part_a_b_c/stop.cpp part_a_b_c/bus.h part_a_b_c/bus.cpp part_a_b_c/station_manager.h part_a_b_c/station_manager.cpp part_a_b_c/request_manager.h part_a_b_c/utils.h part_a_b_c/utils.cpp part_a_b_c/request_manager.cpp part_c/bus.h part_c/bus.cpp part_c/main.cpp part_c/stop.h part_c/stop.cpp part_c/utils.h part_c/utils.cpp part_c/request_manager.h part_c/request_manager.cpp part_c/station_manager.h part_c/station_manager.cpp)
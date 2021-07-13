cmake_minimum_required(VERSION 3.19)
project(coursera_brown_final)

set(CMAKE_CXX_STANDARD 17)
set(APP_DOMAIN ./)
set(APP_PART_A ./part_a)


include_directories(${APP_DOMAIN})
include_directories(${APP_PART_A})


add_executable(coursera_brown_final part_a/main.cpp iterator_range.h profile.h test_runner.h test_runner.cpp part_a/stop.h part_a/stop.cpp part_a/bus.h part_a/bus.cpp part_a/station_manager.h part_a/station_manager.cpp)
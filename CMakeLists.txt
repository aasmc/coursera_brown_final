cmake_minimum_required(VERSION 3.19)
project(coursera_brown_final)

set(CMAKE_CXX_STANDARD 17)
set(APP_DOMAIN ./)
set(APP_PART_A part_a_b)
set(APP_PART_C part_c)
set(APP_PART_D part_d)


include_directories(${APP_DOMAIN})
include_directories(${APP_PART_A})
include_directories(${APP_PART_C})
include_directories(${APP_PART_D})


add_executable(coursera_brown_final part_a_b/main.cpp iterator_range.h profile.h test_runner.h
        test_runner.cpp part_a_b/stop.h part_a_b/stop.cpp part_a_b/bus.h part_a_b/bus.cpp part_a_b/station_manager.h
        part_a_b/station_manager.cpp part_a_b/request_manager.h part_a_b/utils.h part_a_b/utils.cpp part_a_b/request_manager.cpp
        part_c/bus.h part_c/bus.cpp part_c/main.cpp part_c/stop.h part_c/stop.cpp part_c/utils.h
        part_c/utils.cpp part_c/request_manager.h part_c/request_manager.cpp part_c/station_manager.h
        part_c/station_manager.cpp part_d/json.h part_d/json.cpp part_d/bus.h part_d/bus.cpp part_d/json.h part_d/json.cpp
        part_d/main.cpp part_d/request_manager.h part_d/request_manager.cpp part_d/station_manager.h part_d/station_manager.cpp
        part_d/stop.h part_d/stop.cpp part_d/utils.cpp part_d/utils.h part_e/graph.h part_e/router.h)
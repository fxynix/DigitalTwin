cmake_minimum_required(VERSION 3.16)
project(DigitalTwin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS REQUIRED
        Core
        Gui
        Widgets
        Concurrent
)

add_subdirectory(src/main_window)
add_subdirectory(src/memory)
add_subdirectory(src/fault_models)
add_subdirectory(src/algorithms)
add_subdirectory(src/core)
add_subdirectory(src/widget_details)

add_executable(DigitalTwin src/main.cpp)
target_link_libraries(DigitalTwin PRIVATE main_window)

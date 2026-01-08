add_library(algorithms STATIC
    test_algorithm.h
    simple_test.h
    simple_test.cpp
)

target_link_libraries(algorithms PRIVATE
    core
    Qt6::Core
)

target_include_directories(algorithms PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
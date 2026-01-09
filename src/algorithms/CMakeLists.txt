add_library(algorithms STATIC
    test_algorithm.h
    march_c_test.h
    march_c_test.cpp
    checkerboard_test.h checkerboard_test.cpp
    march_lr_test.h march_lr_test.cpp
    mats_plus_plus_test.h mats_plus_plus_test.cpp
)

target_link_libraries(algorithms PRIVATE
    core
    Qt6::Core
)

target_include_directories(algorithms PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

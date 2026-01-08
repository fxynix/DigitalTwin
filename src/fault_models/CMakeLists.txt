add_library(fault_models STATIC
    fault_model.h
    stuck_at_zero.h
    stuck_at_zero.cpp
    stuck_at_one.h stuck_at_one.cpp
)

target_link_libraries(fault_models PRIVATE
    memory
)

target_include_directories(fault_models PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(core STATIC
    faulty_memory.h
    faulty_memory.cpp
)

target_link_libraries(core PRIVATE
    memory
    fault_models
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
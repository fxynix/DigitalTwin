add_library(main_window STATIC
    main_window.h
    main_window.cpp
    main_window.ui
)

target_link_libraries(main_window 
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Concurrent
    PRIVATE
        widget_details
        algorithms
        fault_models
        memory
        core
)

target_include_directories(main_window PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

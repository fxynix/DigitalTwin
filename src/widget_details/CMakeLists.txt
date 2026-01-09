add_library(widget_details STATIC
    widget_details.h
    widget_details.cpp
    widget_details.ui
)

target_link_libraries(widget_details PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(widget_details PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
cmake_policy(VERSION 3.6..3.7)

project(points_play VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(points_play
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generate_point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/marks_plot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/points_player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qwt_plot_picker_ext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qwt_plot_extcurve.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qwt_series_data_ext.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/qwt_point_ext.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qwt_plot_extcurve.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qwt_series_data_ext.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/generate_point.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/marks_plot.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/points_player.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qwt_plot_picker_ext.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/include/points_player.ui

    ${CMAKE_CURRENT_SOURCE_DIR}/files/share/icon.qrc
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui )
target_link_libraries(${PROJECT_NAME} qwt-qt5 )

target_include_directories(points_play PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/ )
target_include_directories(points_play PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include/ )

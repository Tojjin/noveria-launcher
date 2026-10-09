cmake_minimum_required(VERSION 3.16)

project(noveria-launcher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(noveria-launcher
  src/main.cpp
  src/mainwindow.h
  src/mainwindow.cpp
  src/desktopentry.h
  src/desktopparser.h
  src/desktopentry.cpp
  src/desktopparser.cpp
)

target_link_libraries(noveria-launcher PRIVATE Qt6::Widgets)

set_target_properties(noveria-launcher PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)

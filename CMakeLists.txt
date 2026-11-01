cmake_minimum_required(VERSION 3.16)

project(noveria-launcher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Quick QuickControls2)

qt_standard_project_setup()

qt_add_executable(noveria-launcher
  src/main.cpp
  src/mainwindow.h
  src/mainwindow.cpp

  src/desktopentry.h
  src/desktopentry.cpp

  src/desktopparser.h
  src/desktopparser.cpp

  src/desktopentrymodel.h
  src/desktopentrymodel.cpp

  src/desktopentrydelegate.h
  src/desktopentrydelegate.cpp

  src/desktopentryproxymodel.h
  src/desktopentryproxymodel.cpp

  resources/resources.qrc
)

target_link_libraries(noveria-launcher PRIVATE Qt6::Widgets Qt6::Network)

qt_add_executable(noveria-launcher-qml
  src/main-qml.cpp
)

set_source_files_properties(qml/Main.qml PROPERTIES QT_RESOURCE_ALIAS Main.qml)

qt_add_qml_module(noveria-launcher-qml
  URI Noveria
  VERSION 1.0
  QML_FILES
  qml/Main.qml
)

target_link_libraries(noveria-launcher-qml PRIVATE Qt6::Quick Qt6::QuickControls2)

set_target_properties(noveria-launcher PROPERTIES
    WIN32_EXECUTABLE OFF
    MACOSX_BUNDLE OFF
)

include(GNUInstallDirs)

install(TARGETS noveria-launcher
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
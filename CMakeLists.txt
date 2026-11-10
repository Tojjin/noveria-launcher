cmake_minimum_required(VERSION 3.16)

project(noveria-launcher VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 Network)
find_package(tomlplusplus REQUIRED)

qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

qt_add_library(noveria-core STATIC
  src/core/desktopentry.h
  src/core/desktopentry.cpp

  src/core/desktopparser.h
  src/core/desktopparser.cpp

  src/core/desktopentrymodel.h
  src/core/desktopentrymodel.cpp

  src/core/desktopentryproxymodel.h
  src/core/desktopentryproxymodel.cpp
)

target_link_libraries(noveria-core PUBLIC Qt6::Core)
target_include_directories(noveria-core PUBLIC src)

qt_add_executable(noveria-launcher
  src/main.cpp
)

target_include_directories(noveria-launcher PRIVATE src/app)
target_link_libraries(noveria-launcher PRIVATE
  noveria-core
  Qt6::Gui
  Qt6::Quick
  Qt6::QuickControls2
  Qt6::Network
  tomlplusplus::tomlplusplus
)

set_source_files_properties(qml/Main.qml PROPERTIES QT_RESOURCE_ALIAS Main.qml)

qt_add_qml_module(noveria-launcher
  URI Noveria
  VERSION 1.0
  QML_FILES
    qml/Main.qml
  SOURCES
    src/app/launcher.h
    src/app/launcher.cpp
    src/app/iconprovider.h
    src/app/iconprovider.cpp
    src/app/theme.h
    src/app/theme.cpp
)

set_target_properties(noveria-launcher PROPERTIES
  WIN32_EXECUTABLE OFF
  MACOSX_BUNDLE OFF
)

include(GNUInstallDirs)

install(TARGETS noveria-launcher
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES data/noveria-launcher.desktop
  DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

install(FILES data/icons/hicolor/scalable/apps/noveria-launcher.svg
  DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)

install(FILES config.example.toml
  DESTINATION ${CMAKE_INSTALL_DATADIR}/noveria-launcher
)

cmake_minimum_required(VERSION 3.25)
project(shelf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

find_package(Qt6 6.8 REQUIRED COMPONENTS
    Core
    Quick
    QuickControls2
    Gui
    DBus
    WaylandClient
)

find_package(KF6 6.0.0 REQUIRED COMPONENTS
    Config
    Crash
    GlobalAccel
    IconThemes
    Service
    WindowSystem
    I18n
)

find_package(LayerShellQt REQUIRED)
find_package(LibTaskManager REQUIRED)

qt_add_resources(SHELF_RESOURCES qml/qml.qrc)

add_executable(shelf
    src/main.cpp
    src/dockwindow.cpp
    src/dockwindow.h
    src/shelfconfig.cpp
    src/shelfconfig.h
    ${SHELF_RESOURCES}
)

target_link_libraries(shelf PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Gui
    Qt6::DBus
    Qt6::WaylandClient
    KF6::ConfigCore
    KF6::Crash
    KF6::GlobalAccel
    KF6::IconThemes
    KF6::Service
    KF6::WindowSystem
    KF6::I18n
    LayerShellQt::Interface
    PW::LibTaskManager
)

install(TARGETS shelf DESTINATION ${KDE_INSTALL_BINDIR})
install(FILES packaging/shelf.desktop DESTINATION ${KDE_INSTALL_APPDIR})

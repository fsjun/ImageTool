cmake_minimum_required(VERSION 3.16)

project(ImageTool VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick QuickControls2 REQUIRED)

qt_add_executable(appImageTool
    application.qrc main.cpp imageprocess.cpp imageprocess.h ColorImageProvider.cpp ColorImageProvider.h manager.h manager.cpp
)

qt_add_qml_module(appImageTool
    URI ImageTool
    VERSION 1.0
    QML_FILES main.qml Screen01.qml
)

set_target_properties(appImageTool PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appImageTool
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appImageTool
    PRIVATE Qt6::Quick Qt6::QuickControls2)

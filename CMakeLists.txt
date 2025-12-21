cmake_minimum_required(VERSION 3.16)
project(xml_editor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_LIB Qt5::Widgets)
else()
    set(QT_LIB Qt6::Widgets)
endif()

# Core library (all existing .cpp in src/code except main.cpp)
file(GLOB CORE_SOURCES "src/code/*.cpp")
list(FILTER CORE_SOURCES EXCLUDE REGEX "main.cpp$")
add_library(xml_core STATIC ${CORE_SOURCES})
target_include_directories(xml_core PUBLIC src/header)

# CLI executable (existing)
add_executable(xml_editor src/code/main.cpp)
target_link_libraries(xml_editor PRIVATE xml_core)

# GUI executable
add_executable(xml_editor_gui
    src/gui/GuiMain.cpp
    src/gui/MainWindow.cpp
    src/gui/PreviewWindow.cpp
)
target_link_libraries(xml_editor_gui PRIVATE xml_core ${QT_LIB})

# Enable automoc for Qt
set_target_properties(xml_editor_gui PROPERTIES AUTOMOC ON)

# Installation (optional)
install(TARGETS xml_editor xml_editor_gui RUNTIME DESTINATION bin)

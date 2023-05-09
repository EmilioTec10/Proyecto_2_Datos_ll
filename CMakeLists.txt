cmake_minimum_required(VERSION 3.5)

project(Proyecto_2_Datos_ll VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        Main_Window.h
        Main_Window.cpp
        Levels.h
        Levels.cpp
        Pac_Man.h
        Pac_Man.cpp
        Dots.h
        Dots.cpp
        Blocks.h
        Blocks.cpp
        Ghost.h
        Ghost.cpp
        SuperDot.h
        SuperDot.cpp
        Level2.cpp
        Level2.h
        Level3.h
        Level3.cpp
        Level4.h
        Level4.cpp
        AStar.h
        AStar.cpp
        Resources.qrc

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Proyecto_2_Datos_ll
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Proyecto_2_Datos_ll APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Proyecto_2_Datos_ll SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Proyecto_2_Datos_ll
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Proyecto_2_Datos_ll PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Proyecto_2_Datos_ll PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Proyecto_2_Datos_ll
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Proyecto_2_Datos_ll)
endif()

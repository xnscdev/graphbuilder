cmake_minimum_required(VERSION 3.5)

project(graphbuilder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES graphbuilder_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        ${TS_FILES}
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        graphview.cpp
        graphview.h
        commandlist.cpp
        commandlist.h
        fileparser.cpp
        fileparser.h
        blockparams.cpp
        blockparams.h
        labeled/translucentlabel.h
        labeled/labeledwidget.h
        labeled/labeledspinbox.h
        labeled/labeledfontpicker.h
        labeled/labeledtable.h
        labeled/labeledlineedit.h
        block/buildcontext.cpp
        block/buildcontext.h
        block/blockwidget.cpp
        block/blockwidget.h
        block/graphtemplateblock.h
        block/favscaleblock.cpp
        block/favscaleblock.h
        block/setfontblock.cpp
        block/setfontblock.h
        block/data1dblock.cpp
        block/data1dblock.h
        block/titleblock.cpp
        block/titleblock.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(graphbuilder
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET graphbuilder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(graphbuilder SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(graphbuilder
                ${PROJECT_SOURCES}
        )
    endif ()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

target_link_libraries(graphbuilder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(graphbuilder PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(graphbuilder)
endif ()

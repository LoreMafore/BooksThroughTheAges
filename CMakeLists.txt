cmake_minimum_required(VERSION 3.27)
project(BooksThroughTheAges)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.3\\mingw_64")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)


add_executable(BooksThroughTheAges
        main.cpp
        BookInfo.h
        BookInfo.cpp
        Background.h
        resources.qrc
        Buttons.cpp
        Buttons.h
        Books.h
        Books.cpp
        MainWindowOld.h
        MainWindowOld.cpp
        BookSearchWindow.h
        BookSearchWindow.cpp
        BookCard.h
        BookCard.cpp
        BookInfoWindow.h
        BookInfoWindow.cpp
        newsearchwindow.cpp
        newsearchwindow.h
        newsearchwindow.ui
        mainWindow.cpp
        mainWindow.h
        mainWindow.ui
)
target_link_libraries(BooksThroughTheAges
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
)
qt_add_resources(MY_PROJECT_NAME resources.qrc)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    # Copy imageformats plugins directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/")

    # Copy the JPEG image format plugin
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/imageformats/qjpeg${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/")

    # Copy other common image format plugins for completeness
    foreach (IMAGE_FORMAT qgif qico qsvg)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/imageformats/${IMAGE_FORMAT}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/imageformats/")
    endforeach (IMAGE_FORMAT)

    # Make sure to copy the Network DLL as well
    foreach (QT_LIB Core Gui Widgets Network)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
cmake_minimum_required(VERSION 3.24)
project(Tetris)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Tetris
        GameArea.cpp
        GameArea.h
        Item.cpp
        Item.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        NextArea.cpp
        NextArea.h
        rc.qrc
        README.md
        Tetris.pro)

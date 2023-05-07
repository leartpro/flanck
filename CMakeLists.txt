cmake_minimum_required(VERSION 3.24)
project(flanck_gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.4.3_3")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(flanck_gui main.cpp MainWindow.cpp MainWindow.h FlanckSyntaxHighlighter.h FlanckSyntaxHighlighter.cpp OnlyWriteLineEdit.cpp InterpreterWorkerThread.h InterpreterWorkerThread.cpp)
target_link_libraries(flanck_gui
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )


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

add_executable(flanck_gui main.cpp ui/MainWindow.cpp ui/MainWindow.h ui/widgets/FlanckSyntaxHighlighter.h ui/widgets/FlanckSyntaxHighlighter.cpp ui/widgets/OnlyWriteLineEdit.cpp ui/InterpreterWorkerThread.h ui/InterpreterWorkerThread.cpp interpreter/Interpreter.cpp interpreter/Lexer.cpp interpreter/Parser.cpp interpreter/CMDInterpreterObserver.h)
target_link_libraries(flanck_gui
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )


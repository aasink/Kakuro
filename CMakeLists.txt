cmake_minimum_required(VERSION 3.16)
project(KakuroApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(Kakuro
    src/main.cpp
    src/MainWindow.cpp
    src/StartPage.cpp
    src/GamePage.cpp
    src/HelpPage.cpp
    src/GridWidget.cpp
    src/Game/Board.cpp
    src/Game/Generator.cpp
    src/Game/Controller.cpp

    include/MainWindow.h
    include/StartPage.h
    include/GamePage.h
    include/HelpPage.h
    include/GridWidget.h
    include/Game/Board.h
    include/Game/Generator.h
    include/Game/Controller.h   
)

qt_add_resources(Kakuro "styles"
    PREFIX "/"
    FILES resources/style.qss
)

target_include_directories(Kakuro PRIVATE include)
target_include_directories(Kakuro PRIVATE include/Game)
target_link_libraries(Kakuro PRIVATE Qt6::Widgets)

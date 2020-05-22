cmake_minimum_required(VERSION 3.7)
project(QtStarter)
set(CMAKE_CXX_STANDARD 17)

# Tell cmake where Qt is located
set(Qt5_DIR "/usr/local/Cellar/qt/5.14.1/lib/cmake/Qt5")
set(QT_INCLUDES "/usr/local/Cellar/qt/5.14.1/include")
set(QT_INCLUDES "cmake-build-debug/QtStarterStarter_autogen/include/ui_QtStarterMainWindow.h")
MESSAGE("QT_INCLUDES: ${QT_INCLUDES}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON) # if you have any .ui files
set(CMAKE_AUTORCC ON) # if you have any .qrc files

# Find QT packages
include_directories(cmake-build-debug/QtStarterStarter_autogen/include)
find_package(Qt5 COMPONENTS Widgets)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

qt5_generate_moc(QtStarterGame.cpp QtStarterGame.moc QtStarter.cpp QtStarter.moc)

add_executable(${PROJECT_NAME} bullet.cpp     gamemanager.cpp     main.cpp     mainwindow.cpp     player.cpp     ship.cpp bullet.h     gamemanager.h     mainwindow.h     player.h     ship.h res.qrc)

#Link the QtStarter executable to the Qt 5 widgets library.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)



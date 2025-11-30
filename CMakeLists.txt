cmake_minimum_required(VERSION 3.29)
project(launcher LANGUAGES CXX)

option(BUILD_TESTS "Build tests" ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/res)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Concurrent Network)

qt_standard_project_setup()
qt_add_executable(launcher
        src/main.cpp src/launcher.cpp src/window.cpp src/util.cpp src/ProgressDialog.cpp
        src/res/MasterFrame.ui src/res/LoginWidget.ui src/res/MenuWidget.ui src/res/ProgressWidget.ui src/res/master.qrc
        src/include/window.hpp src/include/launcher.hpp src/include/util.hpp src/include/ProgressDialog.hpp
)

target_compile_options(launcher PRIVATE -fno-inline -fno-omit-frame-pointer)

target_include_directories(launcher PRIVATE src/include)

target_link_libraries(launcher PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Concurrent
        Qt::Network
        ssl
        crypto
)

set_target_properties(launcher PROPERTIES
        WIN32_EXECUTABLE TRUE
)

install(TARGETS launcher
        RUNTIME DESTINATION bin/
)

qt6_generate_deploy_app_script(
        TARGET launcher
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
        NO_TRANSLATIONS
)

install(SCRIPT ${deploy_script})

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

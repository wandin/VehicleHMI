cmake_minimum_required(VERSION 3.16)

project(VehicleHMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS SerialBus)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appVehicleHMI
    main.cpp
    CanReceiver.h
    CanReceiver.cpp
    VehicleCanProtocol.h
)

qt_add_qml_module(appVehicleHMI
    URI VehicleHMI

    QML_FILES
        Main.qml
        Speedometer.qml

    SOURCES
        VehicleState.h
        VehicleState.cpp
        SOURCES VehicleCanProtocol.h VehicleCanSpeedEncoder.h
        SOURCES CanReceiver.h CanReceiver.cpp
)

target_include_directories(appVehicleHMI
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVehicleHMI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVehicleHMI
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVehicleHMI
    PRIVATE
    Qt6::Quick
    Qt6::SerialBus
)

target_link_libraries(appVehicleHMI PRIVATE Qt6::SerialBus)

include(GNUInstallDirs)
install(TARGETS appVehicleHMI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(simulator)

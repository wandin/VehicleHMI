cmake_minimum_required(VERSION 3.16)

project(VehicleHMI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick SerialBus)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appVehicleHMI main.cpp)

qt_add_qml_module(appVehicleHMI
    URI VehicleHMI

    QML_FILES
        Main.qml
        Speedometer.qml

    SOURCES
        CanReceiver.cpp
        CanReceiver.h
        VehicleCanProtocol.h
        VehicleCanSpeedEncoder.h
        VehicleState.h
        VehicleState.cpp
)

target_include_directories(appVehicleHMI
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(appVehicleHMI
    PRIVATE
    Qt6::Quick
    Qt6::SerialBus
)

include(GNUInstallDirs)
install(TARGETS appVehicleHMI
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_subdirectory(simulator)

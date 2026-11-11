find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 SerialBus)

qt_add_executable(VehicleSimulator main.cpp)

qt_add_qml_module(VehicleSimulator
    URI VehicleSim
    RESOURCE_PREFIX /qt/qml
    OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/qml/VehicleSim"
    QML_FILES
        SimulatorMain.qml
    SOURCES
        speedtransmitter.h
        speedtransmitter.cpp
)

target_compile_features(VehicleSimulator PRIVATE cxx_std_17)
target_include_directories(VehicleSimulator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
target_link_libraries(VehicleSimulator PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::SerialBus)
set_target_properties(VehicleSimulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

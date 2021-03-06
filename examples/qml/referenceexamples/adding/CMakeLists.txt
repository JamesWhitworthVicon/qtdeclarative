# Generated from adding.pro.

cmake_minimum_required(VERSION 3.14)
project(adding LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples/qml/referenceexamples/adding")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Qml)

add_qt_gui_executable(adding
    main.cpp
    person.cpp person.h
)
target_link_libraries(adding PUBLIC
    Qt::Core
    Qt::Qml
)


# Resources:
set(adding_resource_files
    "example.qml"
)

qt6_add_resources(adding "adding"
    PREFIX
        "/"
    FILES
        ${adding_resource_files}
)

install(TARGETS adding
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

set_target_properties(adding PROPERTIES
    QT_QML_MODULE_INSTALL_QMLTYPES TRUE
    QT_QML_MODULE_VERSION 1.0
    QT_QML_MODULE_URI People
)

qt6_qml_type_registration(adding)

# Generated from CustomModule.pro.

#####################################################################
## CustomModule Generic Library:
#####################################################################

qt_add_cmake_library(CustomModule
    OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/../CustomModule"
    SOURCES
        moduleplugin.cpp
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
)

# Resources:
set(moduleplugin_resource_files
    "ModuleType.qml"
)

qt_add_resource(CustomModule "moduleplugin"
    PREFIX
        "/"
    FILES
        ${moduleplugin_resource_files}
)


#### Keys ignored in scope 1:.:.:CustomModule.pro:<TRUE>:
# IMPORT_FILES = "qmldir"
# TEMPLATE = "lib"

# special case begin
qt_autogen_tools_initial_setup(CustomModule)
file(COPY qmldir
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/../CustomModule"
)
# special case end

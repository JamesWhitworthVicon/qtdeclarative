# Generated from qmltest.pro.

#####################################################################
## QuickTest Module:
#####################################################################

qt_add_module(QuickTest
    GENERATE_METATYPES
    QMAKE_MODULE_CONFIG $${QT.testlib.CONFIG}
    SOURCES
        qtestoptions_p.h
        quicktest.cpp quicktest.h
        quicktestglobal.h
        quicktestresult.cpp quicktestresult_p.h
    DEFINES
        QT_NO_FOREACH
        QT_NO_URL_CAST_FROM_STRING
        QT_BUILD_QMLTEST_LIB # special case
    LIBRARIES
        Qt::CorePrivate
        Qt::Gui
        Qt::QmlPrivate
        Qt::Quick
        Qt::QuickPrivate
        Qt::TestPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Test
    PRIVATE_MODULE_INTERFACE
        Qt::TestPrivate
)

#### Keys ignored in scope 1:.:.:qmltest.pro:<TRUE>:
# MODULE_CONFIG = "$${QT.testlib.CONFIG}"

## Scopes:
#####################################################################

qt_extend_target(QuickTest CONDITION TARGET Qt::Widgets
    DEFINES
        QT_QMLTEST_WITH_WIDGETS
    PUBLIC_LIBRARIES
        Qt::Widgets
)

qt_extend_target(QuickTest CONDITION QT_FEATURE_qml_debug
    DEFINES
        QT_QML_DEBUG_NO_WARNING
)
qt_add_docs(QuickTest
    doc/qtqmltest.qdocconf
)


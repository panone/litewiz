################################################################################
################################################################################

TARGET = testbench
TEMPLATE = app

QT *= core xml
QT -= gui

CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += \
    src/application \
    src/test_case \
    ../classifier

DebugBuild {
    LIBS += \
        ../classifier/debug/libclassifier.a
}

ReleaseBuild {
    LIBS += \
        ../classifier/release/libclassifier.a
}

include(src/application/application.pro)
include(src/test_case/test_case.pro)

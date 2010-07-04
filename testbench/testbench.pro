################################################################################
################################################################################

TARGET = testbench
TEMPLATE = app

QT *= core xml
QT -= gui

CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += ../classifier

DebugBuild {
    LIBS += \
        ../classifier/debug/libclassifier.a
}

ReleaseBuild {
    LIBS += \
        ../classifier/release/libclassifier.a
}

include(src/application/application.pro)

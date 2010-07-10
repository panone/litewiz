################################################################################
################################################################################

TARGET = litewiz
TEMPLATE = app

QT *= core gui

INCLUDEPATH += \
    src/application \
    src/files \
    src/user_interface \
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
include(src/files/files.pro)
include(src/user_interface/user_interface.pro)

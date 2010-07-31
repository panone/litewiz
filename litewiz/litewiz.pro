################################################################################
################################################################################

TARGET = litewiz
TEMPLATE = app

QT *= core gui xml

INCLUDEPATH += \
    src/application \
    src/file_clusters \
    src/files \
    src/items \
    src/session \
    src/user_interface \
    src/variants \
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
include(src/file_clusters/file_clusters.pro)
include(src/files/files.pro)
include(src/items/items.pro)
include(src/session/session.pro)
include(src/user_interface/user_interface.pro)
include(src/variants/variants.pro)

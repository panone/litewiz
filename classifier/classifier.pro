################################################################################
################################################################################

TARGET = classifier
TEMPLATE = lib

QT -= gui

CONFIG += staticlib

INCLUDEPATH += \
    src/extractors

HEADERS += \
    classifier.h

include(src/classifier/classifier.pro)
include(src/extractors/extractors.pro)

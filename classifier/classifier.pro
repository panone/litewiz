################################################################################
################################################################################

TARGET = classifier
TEMPLATE = lib

QT -= gui

CONFIG += staticlib

INCLUDEPATH += \
    src/classifier

HEADERS += \
    classifier.h

include(src/classifier/classifier.pro)

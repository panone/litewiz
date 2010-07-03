################################################################################
################################################################################

TARGET = classifier
TEMPLATE = lib

QT -= gui

CONFIG += staticlib

HEADERS += \
    classifier.h

include(src/classifier/classifier.pro)
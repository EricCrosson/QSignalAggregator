# -*- mode: conf; -*-

TEMPLATE = lib
CONFIG += staticlib
VERSION = 1.0.0

SOURCES += $$files(*.cpp)
HEADERS += $$files(*.h)

DESTDIR = $$LIBDIR
TARGET = qsignalaggregator

# -*- mode: conf;  -*-

TEMPLATE = subdirs

QMAKE_CXXFLAGS += -std=c++11

CONFIG += silent

QT -= gui

test{
  message(Configuring the test build...)
  SUBDIRS += test
} else {
  SUBDIRS += src
}

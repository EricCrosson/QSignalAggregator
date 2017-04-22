# -*- mode: conf;  -*-

TEMPLATE = subdirs

QMAKE_CXXFLAGS += -std=c++14

CONFIG += silent

test{
  message(Configuring the test build...)
  SUBDIRS += test
} else {
  SUBDIRS += src
}

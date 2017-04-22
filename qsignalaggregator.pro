# -*- mode: conf;  -*-

TEMPLATE = subdirs

CONFIG += \
  c++14 \
  silent

QT -= gui

test{
  message(Configuring the test build...)
  SUBDIRS += test
} else {
  SUBDIRS += src
}

# -*- mode: conf;  -*-

TEMPLATE = subdirs

CONFIG += silent

QT -= gui

test{
  message(Configuring the test build...)
  SUBDIRS += test
} else {
  SUBDIRS += src
}

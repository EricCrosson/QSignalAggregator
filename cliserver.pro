# -*- mode: conf;  -*-

TEMPLATE = subdirs

CONFIG += silent

test{
  message(Configuring the test build...)
  SUBDIRS += test
} else {
  SUBDIRS += src
}

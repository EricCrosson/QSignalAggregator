QT += \
  testlib \
  network

TEMPLATE = app

# Testing-harness code
# HEADERS += ../stubs/

# Test-code
SOURCES += $$files(*.cpp)

TARGET = $$BINDIR/$$system(basename $(pwd))

# Code-under-test
INCLUDEPATH += \
  .. \
  ../../src

HEADERS += $$files(../../src/*.h)
SOURCES += $$files(../../src/*.cpp)

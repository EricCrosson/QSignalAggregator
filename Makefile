# Written by Eric Crosson
# 2017-04-04

BUILDDIR=build
DOCDIR=doc

QMAKE_VERSION := $(shell command -v qmake 2> /dev/null)
QMAKE=$(shell which qmake)

all:
ifndef QMAKE_VERSION
$(error "dot is not available please install graphviz")
QMAKE=/opt/Qt/5.8/*_64/bin/qmake
endif

all:
	mkdir -p $(BUILDDIR); \
	cd $(BUILDDIR); \
	$(QMAKE) -spec linux-clang "DEFINES += DEBUG_STARTS_ON" ..; \
	make -j$$(nproc);

.PHONY: test
test:
	mkdir -p $(BUILDDIR); \
	cd $(BUILDDIR); \
	$(QMAKE) -spec linux-clang "CONFIG += test" ..; \
	make -j$$(nproc);

.PHONY: doc
doc:
	doxygen Doxyfile

clean:
	rm -rf $(BUILDDIR) $(DOCDIR)

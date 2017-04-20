# Written by Eric Crosson
# 2017-04-04

BUILDDIR=build
DOCDIR=doc

all:
	mkdir -p $(BUILDDIR); \
	cd $(BUILDDIR); \
	/opt/Qt/5.8/*_64/bin/qmake -spec linux-clang "DEFINES += DEBUG_STARTS_ON" ..; \
	make -j$$(nproc);

.PHONY: test
test:
	mkdir -p $(BUILDDIR); \
	cd $(BUILDDIR); \
	/opt/Qt/5.8/*_64/bin/qmake -spec linux-clang "CONFIG += test" ..; \
	make -j$$(nproc);

.PHONY: doc
doc:
	doxygen Doxyfile

clean:
	rm -rf $(BUILDDIR) $(DOCDIR)

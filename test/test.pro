# -*- mode: conf;  -*-

TEMPLATE = subdirs

# TODO: consider bringing back template and ignoring its presence
# with the find command
SUBDIRS += $$system("find . -mindepth 2 -name '*.pro' -type f")

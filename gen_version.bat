m4 -E <templates\flasher_version.h.m4 >src/flasher_version.h.tmp
cmp -s src/flasher_version.h.tmp src/flasher_version.h || cp src/flasher_version.h.tmp src/flasher_version.h

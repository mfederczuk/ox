#!/usr/bin/make -f

# Copyright (c) 2023 Michael Federczuk
# SPDX-License-Identifier: MPL-2.0 AND Apache-2.0

# <https://www.gnu.org/software/make/manual/html_node/Makefile-Conventions.html>

SHELL = /bin/sh


CC ?= cc
INSTALL ?= install
INSTALL_PROGRAM ?= $(INSTALL)

ifeq "$(CC)" ""
 $(error The variable 'CC' must not be empty)
endif
ifeq "$(INSTALL_PROGRAM)" ""
 $(error The variable 'INSTALL_PROGRAM' must not be empty)
endif


CFLAGS = -std=c99 \
         -Wall -Wextra -Wconversion \
         -pedantic -Wpedantic -pedantic-errors -Werror=pedantic


prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin


override header_file_pathnames != find include/ -name '*.h' -type f
override source_file_pathnames != find src/ -name '*.c' -type f
override object_file_pathnames := $(source_file_pathnames:src/%.c=build/obj/%.o)


.SUFFIXES:


all: build/ox
.PHONY: all


build/ox: $(object_file_pathnames)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $^

# always re-building *every* object file if *any* header file was touched is suboptimal, but for now it should be ok
$(object_file_pathnames): build/obj/%.o: $(header_file_pathnames) src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -c -o $@ $(lastword $^)

clean:
	rm -rf build/
.PHONY: clean


install: build/ox
	$(INSTALL_PROGRAM) -D $< $(DESTDIR)$(bindir)/ox
.PHONY: install

uninstall:
	rm -f $(DESTDIR)$(bindir)/ox
.PHONY: uninstall

lib_LTLIBRARIES = libtdsl.la
include_HEADERS = tdsl_comm.h \
									tdsl_utils.h \
									tdsl_array.h \
									tdsl_bytes.h \
									tdsl_list.h \
									tdsl_hash.h \
									tdsl_tree.h
libtdsl_la_SOURCES = $(include_HEADERS) \
									tdsl_utils.c \
									tdsl_array.c \
									tdsl_bytes.c \
									tdsl_list.c \
									tdsl_hash.c \
									tdsl_tree.c

noinst_PROGRAMS = test
test_SOURCES = test.c
test_CFLAGS = -L. -ltdsl

.PHONY: run
run:
	./test

.PHONY: debug
debug:
	valgrind --leak-check=full .libs/lt-test

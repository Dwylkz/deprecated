SUBDIRS = . test
include_dac_v2dir = $(includedir)/dac/v2
include_dac_v2_HEADERS = Type.h \
												 Error.h \
												 Comm.h \
												 Basic.h \
												 Bytes.h \
												 Wrapper.h \
												 MArray.h \
												 Array.h \
												 IntArray.h \
												 StringArray.h \
												 AddressArray.h \
												 MSet.h \
												 Set.h \
												 IntSet.h \
												 StringSet.h \
												 AddressSet.h \
												 MPair.h \
												 Pair.h \
												 Map.h

noinst_LTLIBRARIES = libdac2.la

libdac2_la_SOURCES = $(include_dac_v2_HEADERS) \
										Comm.c \
										Basic.c \
										Bytes.c \
										Wrapper.c \
										MArray.c \
										Array.c \
										IntArray.c \
										StringArray.c \
										AddressArray.c \
										MSet.c \
										Set.c \
										IntSet.c \
										StringSet.c \
										AddressSet.c \
										MPair.c \
										Pair.c \
										Map.c

bin_SCRIPTS = dac

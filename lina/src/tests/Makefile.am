INCLUDES = -I$(top_srcdir)/include $(all_includes)
METASOURCES = AUTO
bin_PROGRAMS = ldbtest lcalendartest lutilitytest lconvtest lrangetest lfbstadiumtest lmetricstest lservertest lclienttest

ldbtest_SOURCES =  ldbtest.cpp


ldbtest_LDADD = $(top_builddir)/lib/liblina.a -lz

lcalendartest_SOURCES =  lcalendartest.cpp
lcalendartest_LDADD = $(top_builddir)/lib/liblina.a -lz
lutilitytest_SOURCES =  lutilitytest.cpp
lutilitytest_LDADD = $(top_builddir)/lib/liblina.a -lz
lconvtest_SOURCES =  lconvtest.cpp
lrangetest_SOURCES =  lrangetest.cpp
lfbstadiumtest_SOURCES =  lfbstadiumtest.cpp
lfbstadiumtest_LDADD = $(top_builddir)/lib/liblina.a -lz
lconvtest_LDADD = $(top_builddir)/lib/liblina.a -lz
lmetricstest_SOURCES =  lmetricstest.cpp
lmetricstest_LDADD = $(top_builddir)/lib/liblina.a -lz
SUBDIRS = stadiumtest lchat
lservertest_SOURCES =  lservertest.cpp
lclienttest_SOURCES =  lclienttest.cpp
lservertest_LDADD = $(top_builddir)/lib/liblina.a $(top_builddir)/lib/netxx/libnetxx.a -lssl
lclienttest_LDADD = $(top_builddir)/lib/liblina.a $(top_builddir)/lib/netxx/libnetxx.a -lssl

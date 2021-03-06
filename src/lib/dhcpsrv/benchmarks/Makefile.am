SUBDIRS = .

AM_CPPFLAGS  = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dhcpsrv/tests\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

EXTRA_DIST = benchmarks.dox

BENCHMARKS=
if HAVE_BENCHMARK

BENCHMARKS += run-benchmarks

run_benchmarks_SOURCES  = run_benchmarks.cc
run_benchmarks_SOURCES += generic_lease_mgr_benchmark.cc generic_lease_mgr_benchmark.h
run_benchmarks_SOURCES += generic_host_data_source_benchmark.cc generic_host_data_source_benchmark.h
run_benchmarks_SOURCES += memfile_lease_mgr_benchmark.cc
run_benchmarks_SOURCES += parameters.h

if HAVE_MYSQL
run_benchmarks_SOURCES += mysql_lease_mgr_benchmark.cc
run_benchmarks_SOURCES += mysql_host_data_source_benchmark.cc
endif

if HAVE_PGSQL
run_benchmarks_SOURCES += pgsql_lease_mgr_benchmark.cc
run_benchmarks_SOURCES += pgsql_host_data_source_benchmark.cc
endif

if HAVE_CQL
run_benchmarks_SOURCES += cql_lease_mgr_benchmark.cc
run_benchmarks_SOURCES += cql_host_data_source_benchmark.cc
endif

run_benchmarks_CPPFLAGS  = $(AM_CPPFLAGS) $(BENCHMARK_INCLUDES) -Wno-error=overloaded-virtual

if HAVE_MYSQL
run_benchmarks_CPPFLAGS += $(MYSQL_CPPFLAGS)
endif

if HAVE_PGSQL
run_benchmarks_CPPFLAGS += $(PGSQL_CPPFLAGS)
endif

if HAVE_CQL
run_benchmarks_CPPFLAGS += $(CQL_CPPFLAGS)
endif

run_benchmarks_CXXFLAGS = $(AM_CXXFLAGS)

run_benchmarks_LDFLAGS  = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(BENCHMARK_LDFLAGS)

if HAVE_MYSQL
run_benchmarks_LDFLAGS += $(MYSQL_LIBS)
endif

if HAVE_PGSQL
run_benchmarks_LDFLAGS += $(PGSQL_LIBS)
endif

if HAVE_CQL
run_benchmarks_LDFLAGS += $(CQL_LIBS)
endif

run_benchmarks_LDADD  = $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
run_benchmarks_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_benchmarks_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
run_benchmarks_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
run_benchmarks_LDADD += $(top_builddir)/src/lib/dhcpsrv/testutils/libdhcpsrvtest.la
run_benchmarks_LDADD += $(BENCHMARK_LDADD)
run_benchmarks_LDADD += $(LOG4CPLUS_LIBS)
run_benchmarks_LDADD += $(CRYPTO_LIBS)
run_benchmarks_LDADD += $(BOOST_LIBS)
run_benchmarks_LDADD += $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(BENCHMARKS)

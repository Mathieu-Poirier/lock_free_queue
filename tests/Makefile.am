check_PROGRAMS = test_main
TESTS = $(check_PROGRAMS)

test_main_SOURCES = test_main.cpp
test_main_CPPFLAGS = -I$(top_srcdir)/src $(GTEST_CFLAGS)
test_main_LDADD = $(top_builddir)/src/liblock_free_queue.a $(GTEST_LIBS)
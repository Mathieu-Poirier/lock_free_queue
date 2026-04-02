check_PROGRAMS = test_queue
TESTS = $(check_PROGRAMS)

test_queue_SOURCES = test_LockFreeQueue.cpp
test_queue_CPPFLAGS = -I$(top_srcdir)/src $(GTEST_CFLAGS)
test_queue_LDADD = $(top_builddir)/src/liblock_free_queue.a $(GTEST_LIBS)
check_PROGRAMS = test_LockFreeQueue test_LockFreeQueueBuilder test_CLI
TESTS = $(check_PROGRAMS)

test_LockFreeQueue_SOURCES = test_LockFreeQueue.cpp
test_LockFreeQueue_CPPFLAGS = -I$(top_srcdir)/src $(GTEST_CFLAGS)
test_LockFreeQueue_LDADD = $(top_builddir)/src/liblock_free_queue.a $(GTEST_LIBS)

test_LockFreeQueueBuilder_SOURCES = test_LockFreeQueueBuilder.cpp
test_LockFreeQueueBuilder_CPPFLAGS = -I$(top_srcdir)/src $(GTEST_CFLAGS)
test_LockFreeQueueBuilder_LDADD = $(top_builddir)/src/liblock_free_queue.a $(GTEST_LIBS)

test_CLI_SOURCES = test_CLI.cpp
test_CLI_CPPFLAGS = -I$(top_srcdir)/src $(GTEST_CFLAGS)
test_CLI_LDADD = $(top_builddir)/src/liblock_free_queue.a $(GTEST_LIBS)
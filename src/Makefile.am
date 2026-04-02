bin_PROGRAMS = lock_free_queue

noinst_LIBRARIES = liblock_free_queue.a
liblock_free_queue_a_SOURCES = LockFreeQueue.cpp LockFreeQueue.hpp LockFreeQueueBuilder.cpp LockFreeQueueBuilder.hpp

lock_free_queue_SOURCES = main.cpp CLI.cpp CLI.hpp
lock_free_queue_LDADD = liblock_free_queue.a
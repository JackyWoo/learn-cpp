set(CONCURRENTQUEUE_SOURCE_DIR "${LEARN_CPP_SOURCE_DIR}/contrib/concurrentqueue")

add_library(concurrentqueue INTERFACE)
target_include_directories(concurrentqueue SYSTEM PUBLIC INTERFACE $<BUILD_INTERFACE:${CONCURRENTQUEUE_SOURCE_DIR}>)

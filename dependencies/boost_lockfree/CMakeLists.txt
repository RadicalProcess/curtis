add_library(lockfree INTERFACE)

add_library(boost::lockfree ALIAS lockfree)

target_include_directories(lockfree
        INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}")


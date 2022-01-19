add_library(Engine_mocks INTERFACE)

add_library(rp::Engine_mocks ALIAS Engine_mocks)

target_include_directories(Engine_mocks INTERFACE include)

target_link_libraries(Engine_mocks
        INTERFACE
        rp::Engine
        gmock)


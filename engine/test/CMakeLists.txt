
add_executable(EngineTestHost
        source/BufferTestCase.cpp
        source/MessageTestCase.cpp
        source/EngineTestCase.cpp
        source/FactoryTestCase.cpp
        source/ParameterSpecTestCase.cpp
        source/ParameterSpecSetTestCase.cpp
        source/ParameterSyncTestCase.cpp
        source/EngineManagerTestCase.cpp
        source/VisualizationDataTestCase.cpp
        source/VisualizationCacheTestCase.cpp
        source/ValidatorTestCase.cpp
        source/UtilsTestCase.cpp
        source/RingBufferTestCase.cpp
        source/SampleCapacitorTestCase.cpp)

target_link_libraries(EngineTestHost
        rp::Engine
        rp::Engine_mocks
        gtest
        gmock
        gmock_main)

target_compile_features(EngineTestHost PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(EngineTestHost)

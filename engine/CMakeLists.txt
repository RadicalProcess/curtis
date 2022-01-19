add_subdirectory(test)
add_subdirectory(mock)

add_library(Engine
        source/AdditiveProcessor.cpp
        source/Buffer.cpp
        source/DelayProcessor.cpp
        source/Engine.cpp
        source/EngineManager.cpp
        source/Factory.cpp
        source/HoldProcessor.cpp
        source/VisualizationCache.cpp
        source/ParameterSync.cpp
        source/ParameterSpecSet.cpp
        source/PhasorProcessor.cpp
        source/XFaderProcessor.cpp
        source/ZeroXProcessor.cpp
        source/RingBuffer.cpp
        source/SampleCapacitor.cpp
        source/Preset.cpp
        source/Validator.cpp
        )

add_library(rp::Engine ALIAS Engine)

add_custom_command(
        OUTPUT dsp.h
        COMMAND cbindgen --output dsp.h
        WORKING_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR}/../dsp/capi
        )

target_include_directories(Engine PRIVATE include/engine
        PUBLIC include)

target_compile_features(Engine PRIVATE cxx_std_17)

target_link_libraries(Engine PUBLIC
        DSP::DSP
        boost::lockfree
        $<$<CXX_COMPILER_ID:MSVC>:ws2_32>
        $<$<CXX_COMPILER_ID:MSVC>:UserEnv>
        $<$<CXX_COMPILER_ID:MSVC>:bcrypt>)

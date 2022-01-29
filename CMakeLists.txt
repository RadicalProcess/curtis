cmake_minimum_required(VERSION 3.15)
project(curtis VERSION 0.0.0)

if(NOT DEFINED PRODUCT_VERSION)
    set(PRODUCT_VERSION "0.0.0")
endif()
message("Trevor Version = ${PRODUCT_VERSION}")

include(cmake/platforms.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/dependencies/dsp/capi)

add_subdirectory(dependencies)

juce_add_plugin(curtis
    PLUGIN_MANUFACTURER_CODE RdiP
    PLUGIN_CODE Curt
    VST3_CATEGORIES Fx
    BUNDLE_ID com.radical-process.curtis
    COMPANY_NAME "Radical Process"
    VERSION "${PRODUCT_VERSION}"
    FORMATS VST3 AU)

target_include_directories(curtis PRIVATE include)

target_sources(curtis
    PRIVATE
        source/EngineManager.cpp
        source/GlissonPresenter.cpp
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
        source/ParameterSource.cpp
        source/ParameterSync.cpp
        source/StateSync.cpp
        source/TogglePresenter.cpp
        source/PresetManager.cpp
        source/ParameterSpecSet.cpp
        source/Preset.cpp
        )

target_compile_definitions(curtis
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(curtis
    PRIVATE
        juce::juce_audio_utils
        rp::UICore
        boost::lockfree
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_features(curtis PRIVATE cxx_std_17)
target_link_libraries(curtis PRIVATE rp::CurtisCore)

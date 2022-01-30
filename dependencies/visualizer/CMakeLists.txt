add_subdirectory(test)

add_library(Visualizer
    source/Visualizer.cpp
    source/Vbo.cpp
    source/Waveform.cpp
    source/Attribute.cpp
    source/Uniforms.cpp
    source/ZeroX.cpp)

add_library(rp::Visualizer ALIAS Visualizer)

juce_add_binary_data(VisualizerResource
    HEADER_NAME VisualizerResource.h
    NAMESPACE rp::curtis::resource
    SOURCES
    resource/frag.glsl
    resource/vertex.glsl)

target_compile_features(VisualizerResource PUBLIC cxx_std_17)

target_link_libraries(Visualizer
    PUBLIC
    juce::juce_opengl
    juce::juce_gui_basics
    VisualizerResource
    rp::UICore
    rp::CurtisCore)

target_include_directories(Visualizer
    PRIVATE include/visualizer
    PUBLIC include)

target_compile_features(Visualizer PUBLIC cxx_std_17)


juce_add_gui_app(VisualizerTest PRODUCT_NAME "Visualizer Test")

target_sources(VisualizerTest
        PRIVATE
        source/DummyDataProvider.cpp
        source/MainComponent.cpp
        source/Main.cpp)

target_include_directories(VisualizerTest
        PRIVATE include)

target_link_libraries(VisualizerTest
        PRIVATE
        rp::Visualizer)

target_compile_definitions(VisualizerTest
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:UITest,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:UITest,JUCE_VERSION>")

cmake_minimum_required(VERSION 3.22)

project(AudioAppTest VERSION 0.1.0)

juce_add_gui_app(AudioAppTest
    COMPANY_NAME EZ_DSP
    PRODUCT_NAME "JuceAudioAppTest"
)

juce_generate_juce_header(AudioAppTest)

target_sources(AudioAppTest
    PRIVATE
        src/Main.cpp
        src/MainComponent.cpp
)

target_compile_definitions(AudioAppTest
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:AudioAppTest,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:AudioAppTest,JUCE_VERSION>")

target_link_libraries(AudioAppTest
    PRIVATE
        juce::juce_audio_utils
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
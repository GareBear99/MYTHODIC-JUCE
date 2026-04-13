cmake_minimum_required(VERSION 3.22)

project(MYTHODIC VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MYTHODIC_ENABLE_LTO "Enable link time optimization" ON)
option(MYTHODIC_BUILD_TESTS "Build tests" OFF)
option(MYTHODIC_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

if(MSVC)
    add_compile_options(/permissive- /Zc:__cplusplus)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(MYTHODIC_WARNINGS_AS_ERRORS)
        add_compile_options(-Werror)
    endif()
endif()

if(MYTHODIC_ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported)
    if(ipo_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    endif()
endif()

# Expected layout:
#   MYTHODIC/
#   JUCE/                  <- git submodule, or pass -DJUCE_DIR=/path/to/JUCE
if(DEFINED JUCE_DIR)
    add_subdirectory(${JUCE_DIR} JUCE)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    add_subdirectory(JUCE)
else()
    message(FATAL_ERROR "JUCE not found. Add JUCE as a subdirectory or pass -DJUCE_DIR=/path/to/JUCE")
endif()

juce_add_plugin(MYTHODIC
    COMPANY_NAME "TizWildin Entertainment"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    PLUGIN_MANUFACTURER_CODE TzWe
    PLUGIN_CODE Myth
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "MYTHODIC")

juce_generate_juce_header(MYTHODIC)

target_sources(MYTHODIC PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    Source/dsp/AnalysisEngine.h
    Source/dsp/AnalysisEngine.cpp
    Source/dsp/MaskingModel.h
    Source/dsp/MaskingModel.cpp
    Source/dsp/OverlapDecisionCore.h
    Source/dsp/OverlapDecisionCore.cpp
    Source/dsp/OversampledToneCore.h
    Source/dsp/OversampledToneCore.cpp
    Source/dsp/SpatialEngine.h
    Source/dsp/SpatialEngine.cpp
    Source/dsp/RoomFusionEngine.h
    Source/dsp/RoomFusionEngine.cpp
    Source/dsp/SafetyOutput.h
    Source/dsp/SafetyOutput.cpp
    Source/util/Constants.h
    Source/util/MathHelpers.h
    Source/util/ParameterLayout.h
    Source/util/ParameterLayout.cpp
)

target_compile_definitions(MYTHODIC PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(MYTHODIC PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    Source/dsp/AnalysisEngine.h
    Source/dsp/AnalysisEngine.cpp
    Source/dsp/MaskingModel.h
    Source/dsp/MaskingModel.cpp
    Source/dsp/OverlapDecisionCore.h
    Source/dsp/OverlapDecisionCore.cpp
    Source/dsp/OversampledToneCore.h
    Source/dsp/OversampledToneCore.cpp
    Source/dsp/SpatialEngine.h
    Source/dsp/SpatialEngine.cpp
    Source/dsp/RoomFusionEngine.h
    Source/dsp/RoomFusionEngine.cpp
    Source/dsp/SafetyOutput.h
    Source/dsp/SafetyOutput.cpp
    Source/util/Constants.h
    Source/util/MathHelpers.h
    Source/util/ParameterLayout.h
    Source/util/ParameterLayout.cpp
)

#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include <JuceHeader.h>
#include "wiringPi.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component,
                     public juce::AudioIODeviceCallback, 
                      public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&);
    void timerCallback() override;
    void resized() override;
    void audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
                                        float* const* outputChannelData, int numOutputChannels, int numSamples,
                                        const AudioIODeviceCallbackContext &context) override;
    void audioDeviceAboutToStart(AudioIODevice *device) override;
    void audioDeviceStopped() override;                                    
    void getPhaseInc(float sampleRate){
        phase_inc = (2.f * M_PI * frequency) / sampleRate;
    }
    float tick_sin(){
        float sample = amplitude * std::sin(phase);
        phase += phase_inc;
        if (phase >= M_PI * 2.f)
            phase -=  M_PI * 2.f;
        return sample;
    }


private:
    //==============================================================================
    // Your private member variables go here...
    
    float phase, phase_inc;
    float amplitude = 1.0f;
    float frequency = 200.f;
    juce::AudioDeviceManager adm;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

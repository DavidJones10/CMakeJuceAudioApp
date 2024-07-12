#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    adm.initialiseWithDefaultDevices(0,2);
    adm.addAudioCallback(this);
    setSize (600, 400);
    Timer::startTimerHz(60);
    if (gpio.init(BUTTON_1,IN) == -1){
        printf(GPIO_ERROR);
    }
}

MainComponent::~MainComponent(){
    adm.removeAudioCallback(this);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    char state[3] = "OFF";
    if (gpio.gpioRead(BUTTON_1))
        state = "ON"
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Number of callbacks", getLocalBounds(), juce::Justification::centred, true);
    g.drawText(juce::String(state), 250, 230, 100, 40, juce::Justificaiton::centred, true);
}   

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::audioDeviceAboutToStart(AudioIODevice *device){
    float sr = device->getCurrentSampleRate();
    getPhaseInc(sr);
}

void MainComponent::audioDeviceIOCallbackWithContext(const float* const* inputChannelData, int numInputChannels,
                                        float* const* outputChannelData, int numOutputChannels, int numSamples,
                                        const AudioIODeviceCallbackContext &context){
    for (int i=0; i < numSamples; i++){
        float sine = tick_sin();
        outputChannelData[0][i] = sine;
        outputChannelData[1][i] = sine;
    }
}

void MainComponent::audioDeviceStopped(){

}

void MainComponent::timerCallback(){
    repaint();
}
/*
for (int i=0; i < buffer->getNumSamples(); i++){
        float sine = tick_sin();
        buffer->setSample(0, i, sine);
        buffer->setSample(0, i, sine);
    }
    callbacks += 1;

*/
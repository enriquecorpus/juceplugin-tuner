/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TestAudioSourceAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    TestAudioSourceAudioProcessorEditor (TestAudioSourceAudioProcessor&);
    ~TestAudioSourceAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestAudioSourceAudioProcessor& processor;
    Label infoLabel;
    TestAudioSourceAudioProcessor& getProcessor() const
    {
        return static_cast<TestAudioSourceAudioProcessor&> (processor);
    }


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioSourceAudioProcessorEditor)
};

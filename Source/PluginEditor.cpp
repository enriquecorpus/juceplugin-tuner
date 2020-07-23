/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioSourceAudioProcessorEditor::TestAudioSourceAudioProcessorEditor (TestAudioSourceAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (infoLabel);
           infoLabel.setText ("Text input:", juce::dontSendNotification);
           infoLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
           infoLabel.setJustificationType (juce::Justification::right);

    setSize (400, 300);
    startTimerHz(30);
}

TestAudioSourceAudioProcessorEditor::~TestAudioSourceAudioProcessorEditor()
{
}

//==============================================================================
void TestAudioSourceAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TestAudioSourceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    infoLabel.setBounds(0, 0, 200, 50);
}
void TestAudioSourceAudioProcessorEditor::timerCallback()
{
        TestAudioSourceAudioProcessor& ourProcessor = getProcessor();

    
    if (ourProcessor.nextFFTBlockReady)
    {
       
        //TODO GET  FREQUENCY HERE
      
//        ourProcessor.forwardFFT.performFrequencyOnlyForwardTransform (ourProcessor.fftData.data());
        
                       float freq = (44100 * ourProcessor.fftData[256]  / ourProcessor.forwardFFT.getSize());
                           infoLabel.setText((String)freq  ,juce::dontSendNotification);
     

//                for (int i = 0; i < ourProcessor.forwardFFT.getSize()/2; i++)
//                {
//                    float freq = (44100 * ourProcessor.fftData[i]  / ourProcessor.forwardFFT.getSize());
//                    infoLabel.setText((String)freq  ,juce::dontSendNotification);
//
//
//                }
        
        
      
            //Freq = (sampleRate * fftBufferIdx) / bufferSize
            
        
         ourProcessor.nextFFTBlockReady = false;
        
    }
}

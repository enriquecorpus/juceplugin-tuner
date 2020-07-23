/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioSourceAudioProcessor::TestAudioSourceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),forwardFFT (fftOrder)
#endif
{
}

TestAudioSourceAudioProcessor::~TestAudioSourceAudioProcessor()
{
}

//==============================================================================
const String TestAudioSourceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestAudioSourceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioSourceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioSourceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestAudioSourceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestAudioSourceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestAudioSourceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestAudioSourceAudioProcessor::setCurrentProgram (int index)
{
}

const String TestAudioSourceAudioProcessor::getProgramName (int index)
{
    return {};
}

void TestAudioSourceAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TestAudioSourceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void TestAudioSourceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestAudioSourceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
void TestAudioSourceAudioProcessor::pushNextSampleIntoFifo (float sample)
   {
       // if the fifo contains enough data, set a flag to say
       // that the next line should now be rendered..
       if (fifoIndex == fftSize)       // [8]
       {
           if (! nextFFTBlockReady)    // [9]
           {
               std::fill (fftData.begin(), fftData.end(), 0.0f);
               std::copy (fifo.begin(), fifo.end(), fftData.begin());
               forwardFFT.performFrequencyOnlyForwardTransform (fftData.data());
               nextFFTBlockReady = true;
           }

           fifoIndex = 0;
       }

       fifo[(size_t) fifoIndex++] = sample; // [9]
   }

void TestAudioSourceAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    auto chInv = 1.f / float(buffer.getNumChannels());
    
    for (auto s = 0; s < buffer.getNumSamples(); ++s) {
        auto sample = 0.f;
        for(auto ch = 0;ch < buffer.getNumChannels(); ++ch) {
            auto* channelData = buffer.getReadPointer(ch,s);
            sample += *channelData;
        }
        sample *= chInv;
        pushNextSampleIntoFifo (sample);
        
    }
    
}

//==============================================================================
bool TestAudioSourceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TestAudioSourceAudioProcessor::createEditor()
{
    return new TestAudioSourceAudioProcessorEditor (*this);
}

//==============================================================================
void TestAudioSourceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestAudioSourceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestAudioSourceAudioProcessor();
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

// constructor
FirstattemptatasynthAudioProcessor::FirstattemptatasynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

// destructor
FirstattemptatasynthAudioProcessor::~FirstattemptatasynthAudioProcessor()
{
}

//==============================================================================
const juce::String FirstattemptatasynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstattemptatasynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstattemptatasynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstattemptatasynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstattemptatasynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstattemptatasynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstattemptatasynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstattemptatasynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FirstattemptatasynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstattemptatasynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

// guarunteed to be called before audio playback (dont assume that the methods will be called in a specific order, so be safe and put whatever needs to be initialised into all of the methods (??)
void FirstattemptatasynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void FirstattemptatasynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    // resets n that
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstattemptatasynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void FirstattemptatasynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        // audio buffer coming from the daw
//        // read pointer is only readable, write pointer is readable and writeable
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
//        {
//            // e.g. adds gain
//            channelData[sample] *= 2.0;
//        }
//    }
    
    // audio block object
    juce::dsp::AudioBlock<float> block (buffer);
    
    // dsp block
    for (int channel = 0; channel < block.getNumSamples(); ++channel)
    {
        auto* channelData = block.getChannelPointer(channel);
        
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            channelData[sample] *= 4.0;
        }
    }
}

//==============================================================================
bool FirstattemptatasynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FirstattemptatasynthAudioProcessor::createEditor()
{
    return new FirstattemptatasynthAudioProcessorEditor (*this);
}

//==============================================================================
void FirstattemptatasynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    // saving parameters n that
}

void FirstattemptatasynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    // where saved parameters get stuck
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstattemptatasynthAudioProcessor();
}

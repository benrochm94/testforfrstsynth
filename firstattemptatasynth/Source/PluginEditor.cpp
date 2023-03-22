/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstattemptatasynthAudioProcessorEditor::FirstattemptatasynthAudioProcessorEditor (FirstattemptatasynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    // br
    // bool debug = false;
    // jassert(debug);
    // br
    
    setSize (400, 300);
}

FirstattemptatasynthAudioProcessorEditor::~FirstattemptatasynthAudioProcessorEditor()
{
}

//==============================================================================
void FirstattemptatasynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("please dont change the entire code", getLocalBounds(), juce::Justification::centred, 1);
}

void FirstattemptatasynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

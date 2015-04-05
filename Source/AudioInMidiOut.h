/*
  ==============================================================================

    AudioInMidiOut.h
    Created: 15 Mar 2015 12:13:14pm
    Author:  doctorant

  ==============================================================================
*/

#ifndef AUDIOINMIDIOUT_H_INCLUDED
#define AUDIOINMIDIOUT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioInMidiOut : AudioIODeviceCallback
{
    void audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                                           float** outputChannelData, int numOutputChannels,
                                int numSamples);
};



#endif  // AUDIOINMIDIOUT_H_INCLUDED

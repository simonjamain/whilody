/*
  ==============================================================================

    AudioInMidiOut.cpp
    Created: 15 Mar 2015 12:13:14pm
    Author:  doctorant

  ==============================================================================
*/

#include "AudioInMidiOut.h"

void
AudioInMidiOut::audioDeviceIOCallback (const float** inputChannelData, int /*numInputChannels*/,
                            float** outputChannelData, int numOutputChannels,
                            int numSamples)
{
    

    
    // We need to clear the output buffers, in case they're full of junk..
    for (int i = 0; i < numOutputChannels; ++i)
        if (outputChannelData[i] != nullptr)
            FloatVectorOperations::clear (outputChannelData[i], numSamples);
}
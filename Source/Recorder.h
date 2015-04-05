/*
  ==============================================================================

    Recorder.h
    Created: 10 Mar 2015 1:02:47am
    Author:  doctorant

  ==============================================================================
*/

#ifndef RECORDER_H_INCLUDED
#define RECORDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioRecorder
{
    AudioRecorder():audioDeviceManager()
    {
        this->audioDeviceManager.initialiseWithDefaultDevices(2, 2);
    }
private:
    AudioDeviceManager audioDeviceManager;
};



#endif  // RECORDER_H_INCLUDED

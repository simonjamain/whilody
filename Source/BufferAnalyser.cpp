/*
  ==============================================================================

    BufferAnalyser.cpp
    Created: 5 Mar 2015 12:43:05am
    Author:  doctorant

  ==============================================================================
*/

#include "BufferAnalyser.hpp"

#define DETECTION_LEVEL 0.05

BufferAnalyser::~BufferAnalyser()
{
    delete(_fft);
}

uint8
BufferAnalyser::getPitch(const AudioSampleBuffer& buffer, double sampleRate)
{
    double level = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
    if (level < DETECTION_LEVEL)
    {
        throw BelowDetectionLevelException(DETECTION_LEVEL, level);
    }
    
    AudioSampleBuffer fftBuffer(buffer);
    
    _fft->performFrequencyOnlyForwardTransform(fftBuffer.getWritePointer(0));
    
    const float* frequencies = fftBuffer.getReadPointer(0);
    
    float maxValue = 0;
    int maxIndice = 0;
    //start at 1 to avoid f0 = 0 case;
    for (int freqIndice = 1; freqIndice < fftBuffer.getNumSamples()/2; freqIndice++) {
        
        if(frequencies[freqIndice] > maxValue)
        {
            maxValue = frequencies[freqIndice];
            maxIndice = freqIndice;
        }
         
        //printf("%f\n",frequencies[freqIndice]);
    }
    double f0 = (double(maxIndice)/double(fftBuffer.getNumSamples()))*sampleRate;
    
    return (uint8) floor(((log(f0/440.)/log(2)) * 12.) + 69.);//todo: put this in a function
}

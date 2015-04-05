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
    
    /* auto correlation
    int nbSamples = buffer.getNumSamples();
    int lowestPitchOffset = (1.0f/_lowestFreq)*sampleRate;
    int highestPitchOffset = (1.0f/_highestFreq)*sampleRate;
    
    jassert(lowestPitchOffset > highestPitchOffset);
    jassert(lowestPitchOffset < nbSamples);
    jassert(highestPitchOffset >= 0);
    jassert(buffer.getNumChannels() >= 1);
    
    const float * samples = buffer.getReadPointer(0);
    
    //autocorrelation function
    
    double minDistance = 0;
    int minDistanceOffset = 0;
    bool firstDistance = true;
    int peaks = 0;
    
    //cover all analysed frequencies
    int start = highestPitchOffset;
    int end = lowestPitchOffset;
    double distances[(end-start)+1];
    
    for(int offset = start; offset <= end; offset++)
    {
        double distance = 0;
        //histogram comparison
        for (int index = 0; index < nbSamples; index++)
        {
            int offsetIndex = (index + offset) % nbSamples;
            distance += (double) fabsf(samples[index] - samples[offsetIndex]);
        }
        
        //assign first value
        if (firstDistance)
        {
            minDistance = distance;
            minDistanceOffset = offset;
            firstDistance = false;
        }
        
        //keep best score
        if (distance < minDistance)
        {
            minDistance = distance;
            minDistanceOffset = offset;
        }
        
        if (offset > start + 3)
        {
            if(distances[offset-2] > distances[offset-1] && distances[offset-1] < distance)
            {
                peaks++;
            }
        }
        
        distances[offset-highestPitchOffset] = distance;
        printf("%f\n",distances[offset-highestPitchOffset]);
    }
    
    printf("peaks: %d\n",peaks);
    
    
    //convert to freq then note
    double f0 = sampleRate / minDistanceOffset;
    */
    
    return (uint8) floor(((log(f0/440.)/log(2)) * 12.) + 69.);//todo: put this in a function
}

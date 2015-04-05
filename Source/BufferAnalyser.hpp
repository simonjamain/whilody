#ifndef BUFFERANALYSER_HPP_INCLUDED
#define BUFFERANALYSER_HPP_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class BufferAnalyser
{
public:
    ~BufferAnalyser();
    BufferAnalyser(double lowestFreq, double highestFreq)
    :_lowestFreq(lowestFreq),_highestFreq(highestFreq),_fft(new FFT(12, false)){}
    
    uint8 getPitch(const AudioSampleBuffer& buffer, double sampleRate);
private:
    double _lowestFreq;
    double _highestFreq;
    FFT* _fft;
};

class BelowDetectionLevelException : std::exception
{
public:
    
    BelowDetectionLevelException(double detectionLevel, double level)
    :_detectionLevel(detectionLevel), _level(level){};
    
    const char* what() const noexcept
    {
        return String("The input level is to damn low : "+String(_level)+" (min "+String(_detectionLevel)+")").toUTF8();
    }
private:
    double _detectionLevel;
    double _level;
};


#endif  // BUFFERANALYSER_H_INCLUDED

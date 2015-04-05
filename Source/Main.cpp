/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CommandParser.hpp"
#include "BufferAnalyser.hpp"

#define LOWEST_FREQ 20.
#define HIGHEST_FREQ 8000.

#define BUFFER_SIZE 4096

#define USE_LEFT_CHANNEL true
#define USE_RIGHT_CHANNEL false

#define MIDI_CHANNEL 1
#define MIDI_INSTRUMENT 85//choir
#define MIDI_VELOCITY 127
#define MIDI_MICROSECONDS_PER_QUARTER 250000
//TODO: enable/disable dynamic velocity

void addNoteOn(MidiMessageSequence* midiMessageSequence, uint8 noteNumber, double timestamp, bool* isPlaying)
{
    MidiMessage noteOn = MidiMessage::noteOn(MIDI_CHANNEL, noteNumber, (uint8)MIDI_VELOCITY);
    noteOn.setTimeStamp(timestamp);
    midiMessageSequence->addEvent(noteOn);
    *isPlaying = true;
};
void addNoteOff(MidiMessageSequence* midiMessageSequence, uint8 noteNumber, double timestamp, bool* isPlaying)
{
    MidiMessage noteOff = MidiMessage::noteOff(MIDI_CHANNEL, noteNumber, (uint8)MIDI_VELOCITY);
    noteOff.setTimeStamp(timestamp);
    midiMessageSequence->addEvent(noteOff);
    *isPlaying = false;
};

void audioToMidi(InputStream* soundStream, File& outputFile)
{
    AudioFormatManager audioFormatManager;
    audioFormatManager.registerBasicFormats();// TODO: precise which format we want to use?
    ScopedPointer<AudioFormatReader> soundReader = audioFormatManager.createReaderFor(soundStream);

    BufferAnalyser bufferAnalyser(LOWEST_FREQ,HIGHEST_FREQ);
    
    AudioSampleBuffer buffer(soundReader->numChannels, BUFFER_SIZE);
    
    int64 bufferSize = (int64)buffer.getNumSamples();
    int64 startSample = 0;
    int64 totalSamples = soundReader->lengthInSamples;
    
    //midi
    MidiMessageSequence midiMessageSequence;
    midiMessageSequence.addEvent(MidiMessage::tempoMetaEvent(MIDI_MICROSECONDS_PER_QUARTER));
    
    uint8 currNoteNumber = 0;
    bool isPlaying = false;
    
    while(startSample < totalSamples)
    {
        double timestamp = double(startSample) / double(soundReader->sampleRate);
        timestamp *= (double(MIDI_MICROSECONDS_PER_QUARTER)/5000.);
        
        soundReader->read(&buffer, 0, (int)bufferSize, startSample, USE_LEFT_CHANNEL, USE_RIGHT_CHANNEL);
        
        try
        {
            uint8 noteNumber = bufferAnalyser.getPitch(buffer, soundReader->sampleRate);
            
            //do noteOn
            //printf("note: %d\n", note);
            if (!isPlaying)
            {
                addNoteOn(&midiMessageSequence, noteNumber, timestamp, &isPlaying);
                
                printf("noteOn: %d\n", noteNumber);
            }else if (currNoteNumber != noteNumber)
            {
                addNoteOff(&midiMessageSequence, currNoteNumber, timestamp, &isPlaying);
                printf("noteOff: %d\n", currNoteNumber);
                
                addNoteOn(&midiMessageSequence, noteNumber, timestamp, &isPlaying);
                printf("noteOn: %d\n", noteNumber);
            }
            currNoteNumber = noteNumber;
            
        } catch (BelowDetectionLevelException e)
        {
            //do noteOff
            if(isPlaying)
            {
                addNoteOff(&midiMessageSequence, currNoteNumber, timestamp, &isPlaying);
                printf("noteOff: %d (low level)\n", currNoteNumber);
            }
        }
        startSample += bufferSize;
    }
    double timestampEnd = double(totalSamples+bufferSize) / double(soundReader->sampleRate);
    timestampEnd *= (double(MIDI_MICROSECONDS_PER_QUARTER)/5000.);
    midiMessageSequence.addEvent(MidiMessage::allNotesOff(1), timestampEnd);
    //TODO: note off only if last event is noteOn
    
    /*
     MidiMessageSequence midiMessageSequence;
     midiMessageSequence.addEvent(MidiMessage::tempoMetaEvent(250000));
     midiMessageSequence.addEvent(MidiMessage::noteOn(1,69,uint8(127)), 0.);
     midiMessageSequence.addEvent(MidiMessage::allNotesOff(1), 4.);
     //midiMessageSequence.sort();
     */
    MidiFile midiFile;
    midiFile.addTrack(midiMessageSequence);
    midiFile.setTicksPerQuarterNote(32);
    
    outputFile.create();//ensure file exists
    if(!outputFile.deleteFile())//ensure file is empty and can be written
    {
        throw "impossible d'écrire sur le fichier";
    }
    FileOutputStream outputStream(outputFile);
    midiFile.writeTo(outputStream);
    outputStream.flush();
}

int main (int argc, char* argv[])
{
    // Input parsing
    File inputFile;
    File outputFile;
    
    switch (argc) {
        case 2://file dragged on app or used by terminal
        case 3://app used by terminal
            inputFile = File(argv[1]);
            
            if (!inputFile.existsAsFile())
            {
                throw ParsingException("Le fichier d\'entree n\'existe pas.");
            }
            break;
        case 0://open app normally
        default:
            return 0;
            break;
    }
    
    switch (argc) {
        case 3:
            outputFile = File(argv[2]);
            break;
        case 2:
        default:
            // use the same name for midi file
            outputFile = File(inputFile).withFileExtension(String("mid"));
            break;
    }
    
    audioToMidi(new FileInputStream(inputFile), outputFile);
}
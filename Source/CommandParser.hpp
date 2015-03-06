#ifndef COMMANDPARSER_HPP_INCLUDED
#define COMMANDPARSER_HPP_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class CommandParser
{
public:
	CommandParser(const String& commandLine);

	void parse(const String& commandLine);

	bool isEmpty();

	File getInputFile();

	void usage();

	String getOutputFileName();

private:
	bool _empty;
	File _inputFile;
	String _outputFileName;
};

class ParsingException : std::exception
{
public:
    
    ParsingException(const String& message)
    :_message(message){};
    
    const char* what() const noexcept
    {
        return _message.toUTF8();
    }
private:
    String _message;
};

class CommandParserTest : public UnitTest
{
public:
	CommandParserTest() : UnitTest("CommandParser testing") {}
	void runTest()
	{
		beginTest("test1: construction");

		String inputSoundPath(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "testSound.wav");
		String outputMidiPath(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + "testMidi.midi");
		String commandLine(inputSoundPath + " " + outputMidiPath);

        try
        {
            CommandParser commandParser(commandLine);
        } catch (ParsingException e) {
            expect(false, e.what());
        }
        
        
		
		//TODO: test other commands
	}
};

static CommandParserTest commandParserTest;
#endif
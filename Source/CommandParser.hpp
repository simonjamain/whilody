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

class CommandParserTest : public UnitTest
{
public:
	CommandParserTest() : UnitTest("CommandParser testing") {}
	void runTest()
	{
		beginTest("test1: construction");

		String inputSoundPath(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + ".." + File::separatorString + ".." + File::separatorString + "Ressources" + File::separatorString + "testSound.wav");
		String outputMidiPath(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + ".." + File::separatorString + ".." + File::separatorString + "Ressources" + File::separatorString + "testS.midi");
		String commandLine(inputSoundPath + " " + outputMidiPath);


		CommandParser commandParser(commandLine);

		expect(true, "Bad command interpretation.");
		//TODO: test other commands
	}
};

static CommandParserTest commandParserTest;
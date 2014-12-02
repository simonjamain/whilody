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
		CommandParser commandParser("\\..\\..\\Ressources\\testSound.wav \\..\\..\\Ressources\\test.midi");
		expect(true, "Bad command interpretation.");
		//TODO: test other commands
	}
};

static CommandParserTest commandParserTest;
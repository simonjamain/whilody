#include "CommandParser.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

CommandParser::CommandParser(const String& commandLine)
{
	parse(commandLine);
}

void
CommandParser::parse(const String& commandLine)
{
	if (commandLine.length() != 0)
	{

		StringArray commands = StringArray::fromTokens(StringRef(commandLine), false);

		if (commands.size() != 2)
		{
			usage();
		}


		//input file
		String inputFileURI = File::getCurrentWorkingDirectory().getFullPathName() + commands[0];

		File inputFile(inputFileURI);

		if (!inputFile.existsAsFile())
		{
			usage();
		}

		_inputFile = inputFile;

		//outpur file
		String outputFileURI = File::getCurrentWorkingDirectory().getFullPathName() + commands[1];

		_outputFileName = outputFileURI;
		
		_empty = false;
	}
	else
	{
		_empty = true;
	}
}

void
CommandParser::usage()
{
	exit(0);
}

bool
CommandParser::isEmpty()
{
	return _empty;
}

File
CommandParser::getInputFile()
{
	return _inputFile;
}

String
CommandParser::getOutputFileName()
{
	return _outputFileName;
}


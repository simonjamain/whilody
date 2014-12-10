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
		String inputFileURI = commands[0];// request an absolute path

		File inputFile(inputFileURI);

		if (!inputFile.existsAsFile())
		{
			usage();
		}

		_inputFile = inputFile;

		//output file
		String outputFileURI = commands[1];// request an absolute path

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


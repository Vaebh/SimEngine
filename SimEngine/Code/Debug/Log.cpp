#include "../Debug/Log.h"

#include "../Utils/Clock.h"

#include <iostream>
#include <fstream>
#include <algorithm>

Log::Log() :
m_writeToFile(false)
{}

Log::Log(bool in_writeToFile) :
m_writeToFile(in_writeToFile)
{}

Log::~Log()
{
	std::cout << "LOG: " << m_stringStream.str() << std::endl;

	if(m_writeToFile)
	{
		std::string fileName = "../SimEngine/Logging/LOG_" + Clock::Get()->GetProgramStartTime() + ".txt";

		std::ofstream outputStream;
		outputStream.open(fileName, std::ios::app);

		if(outputStream.is_open() && outputStream.good())
			outputStream << m_stringStream.str() << std::endl;
	}
}
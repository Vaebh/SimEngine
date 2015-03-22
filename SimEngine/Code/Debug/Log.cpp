#include "../Debug/Log.h"

#include "../Utils/Clock.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#define LOG_TO_FILE true

Log::~Log()
{
	std::cout << "LOG: " << m_stringStream.str() << std::endl;

	if(LOG_TO_FILE)
	{
		std::string fileName = "../SimEngine/Logging/LOG_" + Clock::Get()->GetProgramStartTime() + ".txt";

		std::ofstream outputStream;
		outputStream.open(fileName, std::ios::app);

		if(outputStream.is_open() && outputStream.good())
			outputStream << m_stringStream.str() << std::endl;
	}
}
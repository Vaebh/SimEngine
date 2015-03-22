#ifndef SIMENGINE_DEBUGLOG
#define SIMENGINE_DEBUGLOG

#include <sstream>

class Log
{
public:
	Log();
	Log(bool in_writeToFile);
	~Log();

	inline std::ostringstream& Get() {return m_stringStream;}

private:
	bool m_writeToFile;
	std::ostringstream m_stringStream;
};

#endif
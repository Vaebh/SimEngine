#ifndef SIMENGINE_DEBUGLOG
#define SIMENGINE_DEBUGLOG

#include <sstream>

class Log
{
public:
	Log() {}
	~Log();

	inline std::ostringstream& Get() {return m_stringStream;}

private:
	std::ostringstream m_stringStream;
};

#endif
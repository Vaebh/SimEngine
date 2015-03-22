#ifndef SIMENGINE_CLOCK
#define SIMENGINE_CLOCK

#include <string>

class Clock
{
public:
	Clock();

	static const Clock* Get();

	const char* GetCurrentTime() const;
	const std::string GetProgramStartTime() const {return m_programStartTime;}

private:
	static Clock* m_clock;

	std::string m_programStartTime;
};

#endif
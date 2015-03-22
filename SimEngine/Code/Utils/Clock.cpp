#include "../Utils/Clock.h"

#include <stddef.h>
#include <time.h>
#include <algorithm>

Clock* Clock::m_clock = NULL;

namespace
{
	tm* GetLocalTime()
	{
		time_t theTime = time(0);

		struct tm* timeinfo;
		return localtime(&theTime);
	}
}

Clock::Clock()
{
	m_programStartTime = asctime(GetLocalTime());

	// Trim the newline
	m_programStartTime.pop_back();

	// Trim unneeded characters
	std::replace(m_programStartTime.begin(), m_programStartTime.end(), ' ', '_');
	std::replace(m_programStartTime.begin(), m_programStartTime.end(), ':', ',');
}

const Clock* Clock::Get()
{
	if(m_clock == NULL)
		m_clock = new Clock();

	return m_clock;
}

const char* Clock::GetCurrentTime() const
{
	return asctime(GetLocalTime());
}
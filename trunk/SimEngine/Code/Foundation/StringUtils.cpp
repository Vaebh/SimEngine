#include "../Foundation/StringUtils.h"

#include <iostream>

std::vector<std::string> ParseText(std::string in_text, std::string in_delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> delimitedStrings;

	while ((pos = in_text.find(in_delimiter)) != std::string::npos) 
	{
		token = in_text.substr(0, pos);
		delimitedStrings.push_back(token);
		in_text.erase(0, pos + in_delimiter.length());
	}

	delimitedStrings.push_back(in_text);

	return delimitedStrings;
}
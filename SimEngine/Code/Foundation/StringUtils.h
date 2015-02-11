#ifndef STRING_UTILS_SIMENGINE
#define STRING_UTILS_SIMENGINE

#include <sstream>
#include <vector>

template <class NumberType>
std::string ConvertNumber(NumberType inNumber)
{
   std::stringstream ss;//create a stringstream
   ss << inNumber;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

template <typename T>
T StringToNumber (std::string& in_text)
{
    std::istringstream ss(in_text);
    T result;
    return ss >> result ? result : 0;
}

std::vector<std::string> ParseText(std::string in_text, std::string in_delimiter);

#endif //include guard
#ifndef STRING_UTILS_SIMENGINE
#define STRING_UTILS_SIMENGINE

#include <sstream>

template <class NumberType>
std::string ConvertNumber(NumberType inNumber)
{
   std::stringstream ss;//create a stringstream
   ss << inNumber;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

#endif //include guard
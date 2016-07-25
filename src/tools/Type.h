/*
** This class is a toolclass 
*/

#pragma once

#include <string>
#include <sstream>
#include <typeinfo>

std::string demangle(const char* name);


/*
** Use to demangle the format from typeid(T).name().
*/
template<class T>
std::string type(const T& t)
{
	return demangle(typeid(t).name());
};

/*
** Convert a T to a string.
*/
template <class T>
inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

// We will use only standard exceptions
#include <stdexcept>

// Lets invent runtime assertion

#ifdef DEBUG
    #define ASSERT(condition, exception)    if (!(condition)) throw (exception);
#else
    #define ASSERT(condition, exception)
#endif

#endif // __UTILS_HPP__

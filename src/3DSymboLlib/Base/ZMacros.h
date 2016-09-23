#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#include "ZStackDumper.h"

#define Z_ASSERT(p)                                 \
    do {                                            \
        if (nullptr == p) {                         \
           LOGGER_ERROR << "[nullptr exception!]";  \
           Z_LOGGER_ERROR_TRACE();                  \
           assert(p);                               \
        }                                           \
    } while(0)


#define Z_LOGGER_ERROR_TRACE()                      \
    do {                                            \
        auto str = StackDumper().DumpStack();       \
        LOGGER_ERROR << str;                        \
    } while(0)





#endif  // BASE_MACROS_H
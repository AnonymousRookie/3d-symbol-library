#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#define Z_ASSERT(p)                                 \
    do {                                            \
        if (nullptr == p) {                         \
           LOGGER_ERROR << "[nullptr exception!]";  \
        }                                           \
    } while(0)



#endif  // BASE_MACROS_H
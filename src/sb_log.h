#ifndef SB_LOG_H
#define SB_LOG_H

// includes: c
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// macro: LOG_INFO
//------------------------------------------------------------------------------
#define SB_LOG_INFO(format, ...) \
        printf("[ INFO ] " format "\n", __VA_ARGS__);

// macro: LOG_ERROR
//------------------------------------------------------------------------------
#define SB_LOG_ERROR(format, ...) \
{ \
        printf("[ ERROR ] " format "\n", __VA_ARGS__); \
        exit(EXIT_FAILURE); \
}

#endif

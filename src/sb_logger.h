#ifndef SB_LOGGER_H
#define SB_LOGGER_H

#include <errno.h>
#include <stdio.h>

#define SB_LOGGER_ERROR(format, ...) \
    printf("[ ERROR ][ %s:%d ] " format "\n", __FILE__, __LINE__, __VA_ARGS__);

#endif

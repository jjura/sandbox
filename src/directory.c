// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "directory.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/stat.h>

// function: directory_exists
//------------------------------------------------------------------------------
bool_t directory_exists(path_t directory)
{
        struct stat info;

        return (!stat(directory, &info) && S_ISDIR(info.st_mode));
}

// function: directory_create
//------------------------------------------------------------------------------
void_t directory_create(path_t directory)
{
        struct stat info;

        if (stat(directory, &info) == -1 && mkdir(directory, 0755))
        {
                LOG_ERROR("Failed directory create: %s", strerror(errno));
        }
}

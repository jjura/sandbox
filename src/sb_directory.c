// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_directory.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/stat.h>

// function: sb_directory_exists
//------------------------------------------------------------------------------
sb_bool_t sb_directory_exists(sb_path_t directory)
{
        struct stat info;

        return (!stat(directory, &info) && S_ISDIR(info.st_mode));
}

// function: sb_directory_create
//------------------------------------------------------------------------------
sb_void_t sb_directory_create(sb_path_t directory)
{
        struct stat info;

        if (stat(directory, &info) == -1 && mkdir(directory, 0755))
        {
                SB_LOG_ERROR("Failed directory create: %s", strerror(errno));
        }
}

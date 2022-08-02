// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_file.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// function: sb_file_create
//------------------------------------------------------------------------------
sb_void_t sb_file_create(sb_path_t path)
{
        sb_i32_t descriptor = open(path, O_CREAT, S_IRUSR | S_IWUSR);

        if (descriptor == -1)
        {
                SB_LOG_ERROR("File file create: %s", strerror(errno));
        }

        close(descriptor);
}

// function: sb_file_read
//------------------------------------------------------------------------------
sb_void_t sb_file_read(sb_path_t path, sb_char_t *buffer, sb_i32_t size)
{
        sb_i32_t descriptor = open(path, O_RDONLY);

        if (read(descriptor, buffer, size) == -1)
        {
                SB_LOG_ERROR("Failed file read: %s", strerror(errno));
        }

        buffer[size - 1] = '\0';
}

// function: sb_file_exists
//------------------------------------------------------------------------------
sb_bool_t sb_file_exists(sb_path_t path)
{
        struct stat info;

        return (!stat(path, &info) && !S_ISDIR(info.st_mode));
}

// function: sb_file_size
//------------------------------------------------------------------------------
sb_i32_t sb_file_size(sb_path_t path)
{
        struct stat info;

        if (stat(path, &info))
        {
                SB_LOG_ERROR("Failed file size: %s", strerror(errno));
        }

        return info.st_size;
}

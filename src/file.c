// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "file.h"

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

// function: file_exists
//------------------------------------------------------------------------------
bool_t file_exists(path_t path)
{
        struct stat info;

        return (!stat(path, &info) && !S_ISDIR(info.st_mode));
}

// function: file_size
//------------------------------------------------------------------------------
i32_t file_size(path_t path)
{
        struct stat info;

        if (stat(path, &info))
        {
                LOG_ERROR("Failed file size: %s", strerror(errno));
        }

        return info.st_size;
}

// function: file_create
//------------------------------------------------------------------------------
void_t file_create(path_t path)
{
        i32_t descriptor = open(path, O_CREAT, S_IRUSR | S_IWUSR);

        if (descriptor == -1)
        {
                LOG_ERROR("File file create: %s", strerror(errno));
        }

        close(descriptor);
}

// function: file_read
//------------------------------------------------------------------------------
void_t file_read(path_t path, char_t *buffer, i32_t size)
{
        i32_t descriptor = open(path, O_RDONLY);

        if (read(descriptor, buffer, size) == -1)
        {
                LOG_ERROR("Failed file read: %s", strerror(errno));
        }

        buffer[size - 1] = '\0';
}

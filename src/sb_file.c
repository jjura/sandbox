#define _GNU_SOURCE

#include "sb_file.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

sb_void_t sb_file_create(sb_char_t *file, sb_i32_t mode)
{
    assert(file);

    sb_i32_t fd = open(file, O_CREAT, mode);

    close(fd);
}

sb_bool_t sb_file_exists(sb_char_t *file)
{
    assert(file);

    struct stat info = { 0 };

    if (stat(file, &info))
    {
        return false;
    }

    return (!S_ISDIR(info.st_mode));
}

sb_size_t sb_file_size(sb_char_t *file)
{
    assert(file);

    struct stat info = { 0 };

    if (stat(file, &info))
    {
        return 0;
    }

    return info.st_size;
}

sb_void_t sb_file_read(sb_char_t *file, sb_char_t *buffer, sb_size_t size)
{
    assert(file);
    assert(buffer);

    sb_i32_t descriptor = open(file, O_RDONLY);

    if (read(descriptor, buffer, size) == -1)
    {
        return;
    }

    buffer[size - 1] = 0;
}

sb_char_t *sb_file_find(sb_char_t *file, sb_char_t *value, sb_char_t delimiter)
{
    assert(file);
    assert(value);

    sb_u64_t size = 0;

    sb_char_t *entry = NULL;
    sb_char_t *result = NULL;

    FILE *fd = fopen(file, "r");

    while (getdelim(&entry, &size, delimiter, fd) != -1)
    {
        sb_char_t *position = strstr(entry, value);

        if (position)
        {
            result = position;
            break;
        }
    }

    fclose(fd);

    return result;
}

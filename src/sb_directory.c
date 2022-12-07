#include "sb_directory.h"
#include "sb_file.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

sb_void_t sb_directory_create(sb_char_t *directory, sb_i32_t mode)
{
    assert(directory);

    mkdir(directory, mode);
}

sb_bool_t sb_directory_exists(sb_char_t *directory)
{
    assert(directory);

    struct stat info;

    return (stat(directory, &info) == 0 && S_ISDIR(info.st_mode));
}

sb_bool_t sb_directory_used(sb_char_t *directory, sb_char_t *argument)
{
    assert(directory);
    assert(argument);

    sb_size_t size = strlen(directory) + 9;
    sb_char_t path[size];

    sprintf(path, "%s/environ", directory);

    if (sb_file_exists(path))
    {
        sb_char_t *entry = sb_file_find(path, "SANDBOX=", 0);

        if (entry)
        {
            entry = entry + 8;

            sb_size_t size_argument = strlen(argument);
            sb_size_t size_entry = strlen(entry);

            return !strncmp(argument, entry, size_argument > size_entry ?
                    size_entry :
                    size_argument);
        }
    }

    return false;
}

sb_bool_t sb_directory_for_each(
        sb_char_t *directory,
        sb_char_t *argument,
        sb_directory_iterator_t iterator)
{
    assert(directory);
    assert(argument);
    assert(iterator);

    DIR *dir = opendir(directory);

    for (struct dirent *dirent = readdir(dir); dirent; dirent = readdir(dir))
    {
        sb_size_t size = strlen(directory) + strlen(dirent->d_name) + 2;
        sb_char_t path[size];

        sprintf(path, "%s/%s", directory, dirent->d_name);

        if (iterator(path, argument))
        {
            closedir(dir);
            return true;
        }
    }

    closedir(dir);
    return false;
}

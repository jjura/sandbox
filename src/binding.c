// includes: project
//------------------------------------------------------------------------------
#include "log.h"
#include "file.h"
#include "binding.h"
#include "directory.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/mount.h>
#include <linux/limits.h>

// function: binding_create
//------------------------------------------------------------------------------
void_t binding_create(binding_t *binding)
{
        binding->offset         = 0;
        binding->offset_max     = 0;
        binding->entry          = NULL;
}

// function: binding_destroy
//------------------------------------------------------------------------------
void_t binding_destroy(binding_t *binding)
{
        free(binding->entry);
}

// function: binding_set
//------------------------------------------------------------------------------
void_t binding_set(binding_t *binding, path_t source, path_t target)
{
        if (binding->offset == binding->offset_max)
        {
                binding->offset_max = binding->offset_max * 2 + 1;
                binding->entry = realloc(
                                binding->entry,
                                binding->offset_max *
                                sizeof(binding_entry_t));
        }

        binding->entry[binding->offset].source = source;
        binding->entry[binding->offset].target = target;
        binding->offset++;
}

// function: binding_mount
//------------------------------------------------------------------------------
void_t binding_mount(binding_t *binding, path_t directory)
{
        char_t path[PATH_MAX];

        for (i32_t i = 0; i < binding->offset; ++i)
        {
                binding_entry_t *entry = binding->entry + i;
                sprintf(path, "%s/%s", directory, entry->target);

                if (directory_exists(entry->source) && !directory_exists(path))
                {
                        directory_create(path);
                }
                else if (file_exists(entry->source) && !file_exists(path))
                {
                        file_create(path);
                }

                if (mount(entry->source, path, NULL, MS_BIND, NULL))
                {
                        LOG_ERROR("Failed binding mount: %s", strerror(errno));
                }
        }
}

// function: binding_unmount
//------------------------------------------------------------------------------
void_t binding_unmount(binding_t *binding, path_t directory)
{
        char_t path[PATH_MAX];

        for (i32_t i = 0; i < binding->offset; ++i)
        {
                sprintf(path, "%s/%s", directory, binding->entry[i].target);

                if (umount(path))
                {
                        LOG_ERROR("Failed binding umount: %s", strerror(errno));
                }
        }
}

// includes: project
//------------------------------------------------------------------------------
#include "sb_log.h"
#include "sb_file.h"
#include "sb_binding.h"
#include "sb_directory.h"

// includes: c
//------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>

// includes: linux
//------------------------------------------------------------------------------
#include <sys/mount.h>
#include <linux/limits.h>

// function: sb_binding_create
//------------------------------------------------------------------------------
sb_void_t sb_binding_create(sb_binding_t *binding)
{
        binding->offset         = 0;
        binding->offset_max     = 0;
        binding->entry          = NULL;
}

// function: sb_binding_destroy
//------------------------------------------------------------------------------
sb_void_t sb_binding_destroy(sb_binding_t *binding)
{
        free(binding->entry);
}

// function: sb_binding_set
//------------------------------------------------------------------------------
sb_void_t sb_binding_set(
                sb_binding_t *binding,
                sb_path_t source,
                sb_path_t target)
{
        if (binding->offset == binding->offset_max)
        {
                binding->offset_max = binding->offset_max * 2 + 1;
                binding->entry = realloc(
                                binding->entry,
                                binding->offset_max *
                                sizeof(sb_binding_entry_t));
        }

        binding->entry[binding->offset].source = source;
        binding->entry[binding->offset].target = target;
        binding->offset++;
}

// function: sb_binding_mount
//------------------------------------------------------------------------------
sb_void_t sb_binding_mount(sb_binding_t *binding, sb_path_t directory)
{
        sb_char_t path[PATH_MAX];

        for (sb_i32_t i = 0; i < binding->offset; ++i)
        {
                sb_binding_entry_t *entry = binding->entry + i;

                sprintf(path, "%s/%s", directory, entry->target);

                if (sb_directory_exists(entry->source))
                {
                        sb_directory_create(path);
                }
                else if (sb_file_exists(entry->source))
                {
                        sb_file_create(path);
                }

                if (mount(entry->source, path, NULL, MS_BIND, NULL))
                {
                        SB_LOG_ERROR("Failed binding mount: %s",
                                        strerror(errno));
                }
        }
}

// function: sb_binding_unmount
//------------------------------------------------------------------------------
sb_void_t sb_binding_unmount(sb_binding_t *binding, sb_path_t directory)
{
        sb_char_t path[PATH_MAX];

        for (sb_i32_t i = 0; i < binding->offset; ++i)
        {
                sprintf(path, "%s/%s", directory, binding->entry[i].target);

                if (umount(path))
                {
                        SB_LOG_ERROR("Failed binding umount: %s",
                                        strerror(errno));
                }
        }
}

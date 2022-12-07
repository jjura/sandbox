#include "sb_overlay.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <sys/mount.h>

static sb_bool_t overlay_required(sb_overlay_t *overlay)
{
    assert(overlay);

    return (overlay->lower &&
            overlay->upper &&
            overlay->work);
}

sb_bool_t sb_overlay_mount(sb_overlay_t *overlay, sb_char_t *directory)
{
    assert(overlay);
    assert(directory);

    if (!overlay_required(overlay))
    {
        return true;
    }

    sb_size_t size =
        strlen(overlay->lower) +
        strlen(overlay->upper) +
        strlen(overlay->work) + 32;

    sb_char_t options[size];

    sprintf(options, "lowerdir=%s,upperdir=%s,workdir=%s",
            overlay->lower,
            overlay->upper,
            overlay->work);

    return !(mount("overlay", directory, "overlay", 0, options));
}

sb_bool_t sb_overlay_umount(sb_overlay_t *overlay, sb_char_t *directory)
{
    assert(overlay);
    assert(directory);

    if (!overlay_required(overlay))
    {
        return true;
    }

    return !(umount(directory));
}

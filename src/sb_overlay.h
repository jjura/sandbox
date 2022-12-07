#ifndef SB_OVERLAY_H
#define SB_OVERLAY_H

#include "sb_type.h"

typedef struct {
    sb_char_t *lower;
    sb_char_t *upper;
    sb_char_t *work;
} sb_overlay_t;

sb_bool_t sb_overlay_mount(sb_overlay_t *overlay, sb_char_t *directory);

sb_bool_t sb_overlay_umount(sb_overlay_t *overlay, sb_char_t *directory);

#endif

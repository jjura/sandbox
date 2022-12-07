#ifndef SB_MOUNT_H
#define SB_MOUNT_H

#include "sb_type.h"
#include "sb_vector.h"

typedef enum {
    SB_MOUNTPOINT_TYPE_BINDING,
    SB_MOUNTPOINT_TYPE_FILESYSTEM,
} sb_mountpoint_type_t;

typedef struct {
    sb_char_t *destination;
    sb_char_t *options;
    sb_char_t *source;
    sb_mountpoint_type_t type;
} sb_mountpoint_t;

sb_bool_t sb_mountpoint_mount(sb_mountpoint_t *mountpoint, sb_char_t *directory);

sb_bool_t sb_mountpoint_mount_all(sb_vector_t *mountpoints, sb_char_t *directory);

sb_bool_t sb_mountpoint_umount(sb_mountpoint_t *mountpoint, sb_char_t *directory);

sb_bool_t sb_mountpoint_umount_all(sb_vector_t *mountpoints, sb_char_t *directory);

#endif

#ifndef SB_CONTAINER_H
#define SB_CONTAINER_H

#include "sb_stack.h"
#include "sb_vector.h"
#include "sb_overlay.h"

typedef struct {
    sb_char_t *command;
    sb_char_t *directory;
    sb_char_t *hostname;
    sb_char_t *shell;
    sb_char_t *username;
    sb_i32_t process;
    sb_stack_t stack;
    sb_vector_t mountpoints;
    sb_overlay_t overlay;
} sb_container_t;

sb_void_t sb_container_create(sb_container_t *container);

sb_void_t sb_container_destroy(sb_container_t *container);

sb_void_t sb_container_execute(sb_container_t *container);

sb_bool_t sb_container_set_command(
        sb_container_t *container,
        sb_char_t *command);

sb_bool_t sb_container_set_username(
        sb_container_t *container,
        sb_char_t *username);

sb_bool_t sb_container_set_directory(
        sb_container_t *container,
        sb_char_t *directory);

sb_bool_t sb_container_set_binding(
        sb_container_t *container,
        sb_char_t *source,
        sb_char_t *destination);

sb_bool_t sb_container_set_filesystem(
        sb_container_t *container,
        sb_char_t *type,
        sb_char_t *destination,
        sb_char_t *options);

sb_bool_t sb_container_set_overlay(
        sb_container_t *container,
        sb_char_t *lower,
        sb_char_t *upper,
        sb_char_t *work);

#endif

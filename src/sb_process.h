#ifndef SB_PROCESS_H
#define SB_PROCESS_H

#include "sb_type.h"
#include "sb_container.h"

sb_void_t sb_process_create(sb_i32_t *process, sb_container_t *container);

sb_void_t sb_process_wait(sb_i32_t *process);

#endif

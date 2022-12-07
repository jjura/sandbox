#include <unistd.h>

#include "sb_console.h"
#include "sb_container.h"
#include "sb_type.h"

sb_i32_t main(sb_i32_t argc, sb_char_t *argv[])
{
    sb_container_t container;
    sb_container_create(&container);
    sb_container_set_filesystem(&container, "proc", "/proc", 0);
    sb_container_set_filesystem(&container, "sysfs", "/sys", 0);
    sb_container_set_filesystem(&container, "tmpfs", "/tmp", 0);
    sb_container_set_filesystem(&container, "tmpfs", "/run", 0);
    sb_container_set_filesystem(&container, "devpts", "/dev/pts", 0);
    sb_container_set_binding(&container, ttyname(STDOUT_FILENO), "/dev/console");

    sb_console_t console;
    sb_console_create(&console, argc, argv);

    if (sb_console_process(&console, &container))
    {
        sb_container_execute(&container);
    }

    sb_container_destroy(&container);
}

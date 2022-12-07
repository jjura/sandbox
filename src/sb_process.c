#define _GNU_SOURCE

#include "sb_file.h"
#include "sb_logger.h"
#include "sb_mountpoint.h"
#include "sb_process.h"

#include <assert.h>
#include <stdlib.h>

#include <grp.h>
#include <pwd.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

static sb_bool_t process_use_environment(
        sb_char_t *directory,
        sb_char_t *username)
{
    assert(directory);
    assert(username);

    struct passwd *passwd = getpwnam(username);

    if (!passwd)
    {
        return false;
    }

    sb_char_t *term = getenv("TERM");

    clearenv();

    setenv("SANDBOX", directory, false);
    setenv("TERM", term, false);
    setenv("USER", passwd->pw_name, false);
    setenv("HOME", passwd->pw_dir, false);
    setenv("SHELL", passwd->pw_shell, false);
    setenv("PATH", "/usr/local/bin:/bin:/usr/bin", false);

    chdir(passwd->pw_dir);

    return true;
}

static sb_bool_t process_use_username(sb_char_t *username)
{
    assert(username);

    struct passwd *passwd = getpwnam(username);

    if (!passwd)
    {
        return false;
    }

    initgroups(passwd->pw_name, passwd->pw_gid);

    setgid(passwd->pw_gid);
    setuid(passwd->pw_uid);

    return true;
}

static sb_bool_t process_use_hostname(sb_char_t *file)
{
    assert(file);

    if (!sb_file_exists(file))
    {
        return false;
    }

    sb_size_t size = sb_file_size(file);
    sb_char_t hostname[size];

    sb_file_read(file, hostname, size);

    if (sethostname(hostname, size))
    {
        return false;
    }

    return true;
}

static sb_bool_t process_use_directory(sb_char_t *directory)
{
    assert(directory);

    return (!chdir(directory) && !chroot(directory));
}

static sb_bool_t process_child_main(sb_container_t *container)
{
    assert(container);

    if (!process_use_directory(container->directory))
    {
        SB_LOGGER_ERROR("Failed setting root: %s", container->directory);

        return EXIT_FAILURE;
    }

    if (!process_use_hostname(container->hostname))
    {
        SB_LOGGER_ERROR("Failed setting hostname: %s", container->hostname);

        return EXIT_FAILURE;
    }

    if (!process_use_username(container->username))
    {
        SB_LOGGER_ERROR("Failed setting username: %s", container->username);

        return EXIT_FAILURE;
    }

    if (!process_use_environment(container->directory, container->username))
    {
        SB_LOGGER_ERROR("Failed setting environment: %s", container->username);

        return EXIT_FAILURE;
    }

    execl(container->shell, container->shell, "-c", container->command, NULL);

    return true;
}

static sb_i32_t process_main(sb_void_t *argument)
{
    assert(argument);

    sb_container_t *container = argument;

    if (!sb_overlay_mount(&container->overlay, container->directory))
    {
        SB_LOGGER_ERROR("Failed mounting overlay: %s", container->directory);

        return EXIT_FAILURE;
    }

    if (!sb_mountpoint_mount_all(&container->mountpoints, container->directory))
    {
        SB_LOGGER_ERROR("Failed mounting mountpoints: %s", container->directory);

        return EXIT_FAILURE;
    }

    sb_i32_t process = fork();

    if (!process)
    {
        return process_child_main(container);
    }

    waitpid(process, NULL, 0);

    if (!sb_mountpoint_umount_all(&container->mountpoints, container->directory))
    {
        SB_LOGGER_ERROR("Failed unmounting mountpoints: %s", container->directory);

        return EXIT_FAILURE;
    }

    if (!sb_overlay_umount(&container->overlay, container->directory))
    {
        SB_LOGGER_ERROR("Failed unmounting overlay: %s", container->directory);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

sb_void_t sb_process_create(sb_i32_t *process, sb_container_t *container)
{
    assert(process);
    assert(container);

    sb_char_t *stack = sb_stack_head(&container->stack);

    sb_i32_t namespaces =
        CLONE_NEWCGROUP |
        CLONE_NEWNS     |
        CLONE_NEWPID    |
        CLONE_NEWUTS    |
        SIGCHLD;

    *process = clone(process_main, stack, namespaces, container);
}

sb_void_t sb_process_wait(sb_i32_t *process)
{
    assert(process);

    waitpid(*process, NULL, 0);
}

/******************************************************************************\
**
**  This file is part of the GenesisBack project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <core/core.h>
# include <signal.h>

static char const *signal_list[] = {
    "SIG_0",
    "SIGHUP",
    "SIGINT",
    "SIGQUIT",
    "SIGILL",
    "SIGTRAP",
    "SIGABRT",
    "SIGBUS",
    "SIGFPE",
    "SIGKILL",
    "SIGUSR1",
    "SIGSEGV",
    "SIGUSR2",
    "SIGPIPE",
    "SIGALRM",
    "SIGTERM",
    "SIGSTKFLT",
    "SIGCHLD",
    "SIGCONT",
    "SIGSTOP",
    "SIGTSTP",
    "SIGTTIN",
    "SIGTTOU",
    "SIGURG",
    "SIGXCPU",
    "SIGXFSZ",
    "SIGVTALRM",
    "SIGPROF",
    "SIGWINCH",
    "SIGIO",
    "SIGPWR",
    "SIGSYS",
    "SIGRTMIN"
};

static void signal_catch(int sig)
{
    panic("Catch signal %s\n", signal_list[sig]);
}

/**
 * Ensure that if a stop signal is triggered, we will close correctly the program 
 */
void signal_init(void)
{
    signal(SIGTSTP, signal_catch);
    signal(SIGINT, signal_catch);
    signal(SIGQUIT, signal_catch);
    signal(SIGTERM, signal_catch);
}

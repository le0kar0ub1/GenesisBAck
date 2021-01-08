# Modules module

The module of the modules which handle the modules.

A module is (staticaly) registered in a built-in section "genesisbackmodules" that the others functions will be able to access in runtime.

```c
struct module
{
    char const name[32];
    char const desc[128];
    enum MODULE_HOOKS const hook;
    bool initialized;
    void (* const init)(void);
    void (* const exit)(void);
    void (* const reset)(void);
    void (* const handler)(void);
    void (* const info)(void);
};
```

This part also handle the program init/exit using 4 hooks. Each module is assigned to a hook and initilized when executing the init function of this hook.
This is working same for the program exit (but starting from the highest hook).

```c
enum MODULE_HOOKS {
    MODULE_HOOK_BOOTSTRAP = 0,
    MODULE_HOOK_CORE = 1,
    MODULE_HOOK_GBA = 2,
    MODULE_HOOK_LAST = 3,
    MODULE_HOOK_MAX = 3
};
```

The highest initialized hook can be set using the macro `CONFIG_INITLEVEL`, defaulting to MAX. The emulation is working from the CORE HOOK, just the CORE (or the debug if in debug routine) and the MMU are running.

This is how a module is registered, a set of function is provided to search a module, execute a reset call (which reset all the higher hooks), call a handler, etc...

```c
# define REGISTER_MODULE(xname, xdesc, xhook, xinit, xexit, xreset, xhandler, xinfo)    \
    __attribute__((__used__, __aligned__(8), __section__("genesisbackmodules")))        \
    static const struct module xname = {                                                \
        .name    = #xname,                                                              \
        .desc    = xdesc,                                                               \
        .hook    = xhook,                                                               \
        .initialized = false,                                                           \
        .init    = xinit,                                                               \
        .exit    = xexit,                                                               \
        .reset   = xreset,                                                              \
        .handler = xhandler,                                                            \
        .info    = xinfo                                                                \
    };
```

The {init/exit}hooks can still work without the modules init/exit but use both offer a nice program control.
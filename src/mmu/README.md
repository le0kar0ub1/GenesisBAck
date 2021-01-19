# MMU module

This is the interface between the emulated GBA memory area and the emulator.

The GBA area is allocated by this module and all the memory access are made here.

There are no check on access, this module is mostly used for the address translation.

## Memory triggers

The modules can register some memory triggers. This is staticaly registered range of address which must trigger a function when a write is performed in the given area.

```c
struct mmu_trigger
{
    const struct module *module;
    const uint32_t start;
    const uint32_t end;
    void (* const exec)(struct mmhit hit);
    bool (* const check)(struct mmhit hit);
    pthread_mutex_t mutex;
    bool running;
    volatile size_t wait;
    volatile size_t work;
};
```

If a `check` function is provided, then this one must be called, if it return false then exit the thread.

Each MMU trigger has its own process as you can see on the given struct.
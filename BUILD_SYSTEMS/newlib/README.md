# Newlib

Newlib is a C standard library designed for embedded systems. It is a collection
of software from various sources, all under free software licenses.

Newlib is known for its portability and is often used in conjunction with GNU
cross-development toolchains. 

The idea of this readme is to document how to implement full linker script, makefile
linker scripts content to implement libc in microcontrollers ARM Cortex-M.

### Syscalls

Newlib is enabled by default when you build a project with arm-none-eabi-gcc.
Indeed, you must explicitly opt-out with `-nostdlib` if you prefer to build your
firmware without it.

The newlib documentation5 calls some functions “system calls”. In short, they
are the handful of things newlib expects the underlying “operating system”. The
complete list follows:

```
_exit, close, environ, execve, fork, fstat, getpid, isatty, kill,
link, lseek, open, read, sbrk, stat, times, unlink, wait, write
```
- **fstat:** returns the status of an open file. The minimal version of this
should identify all files as character special devices. This forces
one-byte-read at a time.

```C
#include <sys/stat.h>
int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}
```

- **lseek:** repositions the file offset of the open file associated with the
file descriptor fd to the argument offset according to the directive whence.
Here we can simply return 0, which implies the file is empty.

```C
int _lseek(int file, int offset, int whence) {
  return 0;
}
```

- **close:** closes a file descriptor fd. Since no file should have gotten
opened, we can just return an error on close:

```C
int _close(int fd) {
  return -1;
}
```

- **write:** writes up to count bytes from the buffer starting at buf to the
file referred to by the file descriptor fd. we will want those bytes to be
written to serial instead.

```C
int _write(int file, char *ptr, int len) {
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
  	__io_putchar(*ptr++);
  }
  return len;
}
```

- **read:** attempts to read up to count bytes from file descriptor fd into the
buffer at buf.

```C
int _read(int file, char *ptr, int len) {
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
    	*ptr++ = __io_getchar();
    }
    return len;
}
```

- **sbrk:** increases the program’s data space by increment bytes. In other
words, it increases the size of the heap.

```C
caddr_t _sbrk(int incr)
{
    extern char end asm("end");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    	heap_end = &end;

    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr)
    {
    	errno = ENOMEM;
    	return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}
```

The other functions simple implementation can be found in the file
[syscalls.c](Linkers/syscalls.c). Also can be found more details in the
official documentation from newlib: [newlibc](https://sourceware.org/newlib/).

### Linker



---

### References

[The most thoroughly commented linker script (probably)](https://blog.thea.codes/the-most-thoroughly-commented-linker-script/)

[From Zero to main(): Bootstrapping libc with Newlib](https://interrupt.memfault.com/blog/boostrapping-libc-with-newlib)

[How a Microcontroller starts](https://www.youtube.com/watch?v=MhOba73z-dQ&ab_channel=ArtfulBytes)


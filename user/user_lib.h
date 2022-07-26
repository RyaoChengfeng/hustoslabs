/*
 * header file to be used by applications.
 */

#include "unistd.h"
#include "fcntl.h"
#include "util/types.h"

int printu(const char *s, ...);
int exit(int code);
void* naive_malloc();
void naive_free(void* va);
int fork();
void yield();

// added @lab4_1
int uartputchar(char ch);
int uartgetchar();
int uart2putchar(char ch);
void car_control(char val);

// added @lab4_2
#define PROT_READ  0x1     // Page can be read.
#define PROT_WRITE 0x2     // Page can be written.
#define PROT_EXEC  0x4     // Page can be executed.
#define PROT_NONE  0x0     // Page can not be accessed.
#define PROT_GROWSDOWN 0x01000000  // Extend change to start of growsdown vma (mprotect only).
#define PROT_GROWSUP   0x02000000  // Extend change to start of growsup vma (mprotect only).

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED 0x01        // Share changes.
#define MAP_PRIVATE    0x02    // Changes are private.
# define MAP_SHARED_VALIDATE   0x03    // Share changes and validate extension flags.
# define MAP_TYPE  0x0f        // Mask for type of mapping.

int do_fork();
int do_sleep();
char *allocate_page();
void free_page(char *);
void yield();
char *allocate_share_page();

int do_open(const char *pathname, int flags);
int do_write(int fd, void *buf, uint64 count);
int do_close(int fd);
int do_ioctl(int fd, uint64 request, void *data);
void *do_mmap(void *addr, uint64 length, int prot, int flags, int fd, int64 offset);
int do_munmap(void *addr, uint64 length);
int read_mmap(char *dstva, char *src, uint64 count);

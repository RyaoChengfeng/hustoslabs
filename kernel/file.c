#include "pmm.h"
#include "riscv.h"
#include "process.h"
#include "util/functions.h"
#include "spike_interface/spike_file.h"
#include "spike_interface/spike_utils.h"

#define MMAP_MEM_SIZE 2
typedef struct {
    uint64 addr, length, num;
} mmap_t;
mmap_t mmap_mem[MMAP_MEM_SIZE];

int read_mmap(char *addr, int length, char *buf) {
    for (int i = 0; i < MMAP_MEM_SIZE; i++) {
        if ((uint64)addr >= mmap_mem[i].addr
                && length <= mmap_mem[i].length) {
            return frontend_syscall(HTIFSYS_readmmap, mmap_mem[i].num,
                    (uint64)addr - mmap_mem[i].addr, length,
                    (uint64)buf, 0, 0, 0);
        }
    }
    return -1;
}
int do_open(char *pathname, int flags) {
    // TODO (lab4_3): call host open through spike_file_open and then bind fd to spike_file
    // hint: spike_file_dup function can bind spike_file_t to an int fd.
    panic( "You need to finish open function in lab4_3.\n" );
}
int do_write(int fd, char *buf, uint64 count) {
    spike_file_t *f = spike_file_get(fd);
    return spike_file_write(f, buf, count);
}
int do_close(int fd) {
    spike_file_t *f = spike_file_get(fd);
    return spike_file_close(f);
}

int do_ioctl(int fd, uint64 request, char *data) {
    // TODO (lab4_3): call host ioctl through frontend_sycall
    // hint: frontend_syscall ioctl argument:
    // 1.call number
    // 2.fd
    // 3.the order to device
    // 4.data address
    panic( "You need to call host's ioctl by frontend_syscall in lab4_3.\n" );
}
char *do_mmap(char *addr, uint64 length, int prot, int flags, int fd, int64 offset) {
    for (int i = 0; i < MMAP_MEM_SIZE; i++) {
        if (mmap_mem[i].length == 0) {
            int64 r = frontend_syscall(HTIFSYS_mmap, (uint64)addr, length,
                    prot, flags, spike_file_get(fd)->kfd, offset, 0);
            if (r >= 0) {
                mmap_mem[i].addr = g_ufree_page;
                g_ufree_page += ROUNDUP(length, PGSIZE);
                mmap_mem[i].length = length;
                mmap_mem[i].num = r;
                return (char *)mmap_mem[i].addr;
            } else return (char *)-1;
        }
    }
    return (char *)-1;
}
int do_munmap(char *addr, uint64 length) {
    for (int i = 0; i < MMAP_MEM_SIZE; i++) {
        if (mmap_mem[i].addr == (uint64)addr
                && mmap_mem[i].length == length) {
            int64 r = frontend_syscall(HTIFSYS_munmap, mmap_mem[i].num, length, 0, 0, 0, 0, 0);
            if (r >= 0) mmap_mem[i].length = 0;
            return r;
        }
    }
    return -1;
}

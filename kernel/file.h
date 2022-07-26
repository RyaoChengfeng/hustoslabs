int do_open(char *pathname, int flags);
int do_write(int fd, char *buf, uint64 count);
int do_close(int fd);
int do_ioctl(int fd, uint64 request, char *data);
void *do_mmap(char *addr, uint64 length, int prot, int flags, int fd, int64 offset);
int do_munmap(char *addr, uint64 length);
int read_mmap(char *addr, int length, char *buf);

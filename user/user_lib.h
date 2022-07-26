/*
 * header file to be used by applications.
 */

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

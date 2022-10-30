#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

// Proj 1 implement
void halt(void);
void exit(int status);
int exec(const char *cmd_line);
int wait(int pid);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
int fibo(int n);
int max4(int a, int b, int c, int d);
void check_address(void *addr);

#endif /* userprog/syscall.h */

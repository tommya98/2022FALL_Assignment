#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

// Proj 2 implement
#include <stdbool.h>

void syscall_init (void);

// Proj 1 implement
void halt(void);
void exit(int status);
int exec(const char *cmd_line);
int wait(int pid);
// int read(int fd, void *buffer, unsigned size);
// int write(int fd, const void *buffer, unsigned size);
int fibo(int n);
int max4(int a, int b, int c, int d);
void check_address(void *addr);

// Proj 2 implement
bool create(const char *file, unsigned initial_size);
bool remove(const char *file);
int open(const char *file);
void close(int fd);
int filesize(int fd);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void seek(int fd, unsigned position);
unsigned tell(int fd);

#endif /* userprog/syscall.h */

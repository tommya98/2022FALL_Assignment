#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

// Proj 1 implement
void check_address(void *addr);
void halt(void);
void exit(int status);
int exec(const char *cmd_line);
int wait(int pid);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);

#endif /* userprog/syscall.h */

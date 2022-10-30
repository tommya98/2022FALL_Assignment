#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

// Proj 1 implement : System Call Handler
static void
syscall_handler (struct intr_frame *f UNUSED) {
  int syscall_number = *(uint32_t *)f->esp;

  switch(syscall_number) {
    case SYS_HALT:
      halt();
      break;

    case SYS_EXIT:
      check_address(f->esp+4);
      exit((int)*(uint32_t*)(f->esp+4));
      break;

    case SYS_EXEC:
      check_address(f->esp+4);
      f->eax = exec((char*)*(uint32_t*)(f->esp+4));
      break;

    case SYS_WAIT:
      check_address(f->esp+4);
      f->eax = wait((int)*(uint32_t*)(f->esp+4));
      break;

    case SYS_READ:
      check_address(f->esp+4);
      check_address(f->esp+8);
      check_address(f->esp+12);
		  f->eax = read((int)*(uint32_t*)(f->esp+4), (void*)*(uint32_t*)(f->esp+8), (unsigned)*(uint32_t*)(f->esp+12));
      break;

    case SYS_WRITE:
      check_address(f->esp+4);
      check_address(f->esp+8);
      check_address(f->esp+12);
		  f->eax = write((int)*(uint32_t*)(f->esp+4), (const void*)*(uint32_t*)(f->esp+8), (unsigned)*(uint32_t*)(f->esp+12));
      break;
  }
}

void halt(void) {
  shutdown_power_off();
}

void exit(int status) {
	printf("%s: exit(%d)\n", thread_name(), status);
  thread_current()->exit_status = status;
	thread_exit();
}

int exec(const char *cmd_line) {
  return process_execute(cmd_line);
}

int wait(int pid) {
  return process_wait(pid);
}

int read(int fd, void *buffer, unsigned size) {
  if(fd == 0) {
    for(int i = 0; i < size; i++){
      uint8_t c = input_getc();
      if(c == '\0') {
        break;
      }
    } return size;
  }
  else {
    return -1;
  }
}

int write(int fd, const void *buffer, unsigned size) {
  if(fd == 1) {
		putbuf(buffer, size);
		return size;
  }
  else {
    return -1;
  }
}

// Proj 1 implement : checks the validity of given User Memory Access
void check_address(void *addr) {
  if(addr == NULL) {
    exit(-1);
  }
  if(is_kernel_vaddr(addr)) {
    exit(-1);
  }
  if(is_user_vaddr(addr) == 0) {
    exit(-1);
  }
  if(pagedir_get_page(thread_current()->pagedir, addr) == NULL) {
   	exit(-1);
  }
}
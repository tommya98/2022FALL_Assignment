#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "filesys/off_t.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "devices/shutdown.h"
#include "devices/input.h"

struct file 
  {
    struct inode *inode;        /* File's inode. */
    off_t pos;                  /* Current position. */
    bool deny_write;            /* Has file_deny_write() been called? */
  };

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

    // case SYS_READ:
    //   check_address(f->esp+4);
    //   check_address(f->esp+8);
    //   check_address(f->esp+12);
		//   f->eax = read((int)*(uint32_t*)(f->esp+4), (void*)*(uint32_t*)(f->esp+8), (unsigned)*(uint32_t*)(f->esp+12));
    //   break;

    // case SYS_WRITE:
    //   check_address(f->esp+4);
    //   check_address(f->esp+8);
    //   check_address(f->esp+12);
		//   f->eax = write((int)*(uint32_t*)(f->esp+4), (const void*)*(uint32_t*)(f->esp+8), (unsigned)*(uint32_t*)(f->esp+12));
    //   break;

    case SYS_FIBO:
      check_address(f->esp+4);
      f->eax = fibo((int)*(uint32_t*)(f->esp+4));
      break;

    case SYS_MAX4:
      check_address(f->esp+4);
      check_address(f->esp+8);
      check_address(f->esp+12);
      check_address(f->esp+16);
      f->eax = max4((int)*(uint32_t*)(f->esp+4), (int)*(uint32_t*)(f->esp+8), (int)*(uint32_t*)(f->esp+12), (int)*(uint32_t*)(f->esp+16));
      break;

    // Proj 2 implement
    case SYS_CREATE:
      check_address(f->esp+4);
      check_address(f->esp+8);
      f->eax = create((const char*)*(uint32_t*)(f->esp+4), (unsigned)*(uint32_t*)(f->esp+8));
      break;

    case SYS_REMOVE:
      check_address(f->esp+4);
      f->eax = remove((const char*)*(uint32_t*)(f->esp+4));
      break;

    case SYS_OPEN:
      check_address(f->esp+4);
      f->eax = open((const char*)*(uint32_t*)(f->esp+4));
      break;

    case SYS_CLOSE:
      check_address(f->esp+4);
      close((int)*(uint32_t*)(f->esp+4));
      break;

    case SYS_FILESIZE:
      check_address(f->esp+4);
      f->eax = filesize((int)*(uint32_t*)(f->esp+4));
      break;

    case SYS_READ:
      if(is_user_vaddr((void*)*(uint32_t*)(f->esp+8)) == 0) {
        exit(-1);
      }
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

    case SYS_SEEK:
      check_address(f->esp+4);
      check_address(f->esp+8);
      seek((int)*(uint32_t*)(f->esp+4), (unsigned)*(uint32_t*)(f->esp+8));
      break;

    case SYS_TELL:
      check_address(f->esp+4);
      f->eax = tell((int)*(uint32_t*)(f->esp+4));
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

// int read(int fd, void *buffer, unsigned size) {
//   if(fd == 0) {
//     for(int i = 0; i < size; i++){
//       uint8_t c = input_getc();
//       if(c == '\0') {
//         break;
//       }
//     } return size;
//   }
//   else {
//     return -1;
//   }
// }

// int write(int fd, const void *buffer, unsigned size) {
//   if(fd == 1) {
// 		putbuf(buffer, size);
// 		return size;
//   }
//   else {
//     return -1;
//   }
// }

// Proj 1 implement
int fibo(int n) {
  int a = 1, b = 1, c = 1;
  if(n == 1 || n == 2) {
    return 1;
  }
  else {
    for(int i = 0; i < n - 2; i++) {
      c = a + b;
      a = b;
      b = c;
    }
    return c;
  }
}

int max4(int a, int b, int c, int d) {
  int max = a;
  if(b > max) {
    max = b;
  }
  if(c > max) {
    max = c;
  }
  if(d > max) {
    max = d;
  }

  return max;
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

// Proj 2 implement
bool create(const char *file, unsigned initial_size) {
  if(file == NULL) {
    exit(-1);
  }
  bool ret;

  lock_acquire(&file_lock);
  ret = filesys_create(file, initial_size);
  lock_release(&file_lock);

  return ret;
}

bool remove(const char *file) {
  bool ret;

  lock_acquire(&file_lock);
  ret = filesys_remove(file);
  lock_release(&file_lock);

  return ret;
}

int open(const char *file) {
  if(file == NULL) {
    return -1;
  }

  lock_acquire(&file_lock);

  struct file *fp = filesys_open(file);
  if(fp == NULL) {
    lock_release(&file_lock);
    return -1;
  }

  struct thread *t = thread_current();
  for(int i = 3; i < 128; i++) {
    if(t->fd_array[i] == NULL) {
      if (strcmp(t->name, file) == 0) {
        file_deny_write(fp);
      }
      t->fd_array[i] = fp;
      lock_release(&file_lock);
      return i;
    }
  }
  lock_release(&file_lock);
  return -1;
}

void close(int fd) {
  lock_acquire(&file_lock);
  struct thread *t = thread_current();
  file_close(t->fd_array[fd]);
  t->fd_array[fd] = NULL;
  lock_release(&file_lock);
}

int filesize(int fd) {
  int ret;
  lock_acquire(&file_lock);
  struct thread *t = thread_current();
  ret = file_length(t->fd_array[fd]);
  lock_release(&file_lock);
  return ret;
}

int read(int fd, void *buffer, unsigned size) {
  lock_acquire(&file_lock);
  if(fd == 0) {
    for(int i = 0; i < (int)size; i++){
      uint8_t c = input_getc();
      if(c == '\0') {
        break;
      }
    } 
    lock_release(&file_lock);
    return size;
  }
  else if(fd > 2) {
    int ret;
    struct thread *t = thread_current();
    if(t->fd_array[fd] == NULL) {
      lock_release(&file_lock);
      exit(-1);
    }
    ret = file_read(t->fd_array[fd], buffer, size);
    lock_release(&file_lock);
    return ret;
  }
  else {
    lock_release(&file_lock);
    return -1;
  }
}

int write(int fd, const void *buffer, unsigned size) {
  lock_acquire(&file_lock);
  if(fd == 1) {
		putbuf(buffer, size);
    lock_release(&file_lock);
		return size;
  }
  else if(fd > 2){
    int ret;
    struct thread *t = thread_current();
    if(t->fd_array[fd] == NULL) {
      lock_release(&file_lock);
      exit(-1);
    }
    if (t->fd_array[fd]->deny_write) {
      file_deny_write(t->fd_array[fd]);
    }
    ret = file_write(t->fd_array[fd], buffer, size);
    lock_release(&file_lock);
    return ret;
  }
  else {
    lock_release(&file_lock);
    return -1;
  }
}

void seek(int fd, unsigned position) {
  lock_acquire(&file_lock);
  struct thread *t = thread_current();
  file_seek(t->fd_array[fd], position);
  lock_release(&file_lock);
}

unsigned tell(int fd) {
  unsigned ret;
  lock_acquire(&file_lock);
  struct thread *t = thread_current();
  ret = file_tell(t->fd_array[fd]);
  lock_release(&file_lock);
  return ret;
}
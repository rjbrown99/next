#include <sys/dir.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <sys/param.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <mach/mach.h>
#ifndef _POSIX_SOURCE
 #include "ntypes.h"
 #include "nlimits.h"
 #include "nsignal.h"
 #include "nutsname.h"
 #include "nsyscall.h"
#else
 #include <sys/types.h>
 #include <limits.h>
 #include <signal.h>
 #include <sys/utsname.h>
 #include <syscall.h>
#endif


int
mkfifo (const char *path, mode_t mode)
{
  dev_t dev = 0;
  return mknod (path, mode | S_IFIFO, &dev);
}


//extern char* strdup(const char*);
/*
int
munmap(void *addr, size_t len){
  kern_return_t err;
if (err = vm_deallocate (mach_task_self (),
                             (vm_address_t) addr, (vm_size_t) len))
    {
      errno = err;
      return -1;
    }
  return 0;
}
*/
/*
caddr_t
mmap(caddr_t addr, size_t len, int prot, int flags,
          int fildes, off_t off)
{
        return (caddr_t) syscall (SYS_mmap, addr, len, prot, flags, fildes, off);
}

int
munmap(caddr_t addr, size_t len)
{
        return syscall (SYS_munmap, addr, len);
}

int
mprotect(caddr_t addr, size_t len, int prot)
{
        return syscall (SYS_mprotect, addr, len, prot);
}
*/

caddr_t mmap(caddr_t addr, size_t len, int prot, int flags,
          int fildes, off_t off)
{
        kern_return_t ret_val;
        
        /*      First map ...
        */
        ret_val = map_fd ( fildes,                                      /* fd                           */
                          (vm_offset_t) off,            /* offset                       */
                                          (vm_offset_t*)&addr,          /* address                      */
                                          TRUE,                                         /* find_space           */
                                          (vm_size_t) len);                     /* size                         */

        if (ret_val != KERN_SUCCESS) {
        mach_error("Error calling map_fd() in mmap", ret_val );
                return (caddr_t)0;
        }
        
        /*      ... then protect (this is probably bad)
        */
        ret_val = vm_protect( task_self(),                      /* target_task          */
                                                 (vm_address_t)addr,    /* address                      */
                                                 (vm_size_t) len,               /* size                         */
                                                 FALSE,                                 /* set_maximum          */
                                                 (vm_prot_t) prot);             /* new_protection       */
        if (ret_val != KERN_SUCCESS) {
                mach_error("vm_protect in mmap()", ret_val );
                return (caddr_t)0;
        }
        
        return addr;
}

int munmap(caddr_t addr, size_t len)
{
        kern_return_t ret_val;

        ret_val = vm_deallocate(task_self(),
                                                        (vm_address_t) addr,
                                                        (vm_size_t) len);

        if (ret_val != KERN_SUCCESS) {
                mach_error("vm_deallocate in munmap()", ret_val);
                return -1;
        }
        
        return 0;
}


int
setpgid(pid_t pid, pid_t pgrp){
	return setpgrp((int) pid,(int) pgrp);
}
/*
void
rewinddir(DIR *dirp){
  lseek (dirp->dd_fd, (off_t) 0, SEEK_SET);
  dirp->dd_loc = 0;
  dirp->dd_size = 0;
}
*/
int
uname(struct utsname *name){
return syscall(SYS_uname,name);
}


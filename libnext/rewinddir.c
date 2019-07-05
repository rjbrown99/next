#include <sys/types.h>
#include <sys/dir.h>

void rewinddir(DIR *);

void rewinddir(DIR* dirp) {
//  lseek (dirp->dd_fd, (off_t) 0, SEEK_SET);
//  dirp->dd_loc = 0;
//  dirp->dd_size = 0;
}


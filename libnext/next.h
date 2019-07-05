//typedef long    off_t;
#ifdef OS_FILE
        typedef int     ssize_t;
        typedef int     pid_t;
//        typedef unsigned short  mode_t;
        typedef short   nlink_t;

#endif
#ifdef NEED_MODE_T
typedef unsigned short  mode_t;
#endif


#define ARG_MAX         40960  /* Length of arguments to    */
                               /* exec (include environ)    */
#define CHILD_MAX       100    /* processes per uid         */
#define OPEN_MAX        256    /* open files per process    */
#define MAX_CANON       256    /* bytes in a terminal       */
                               /* canonical input line.     */
#define MAX_INPUT       512    /* Minimum number of bytes   */
                               /* for which space will be   */
                               /* available in a terminal   */
                               /* input queue.              */
#define LINK_MAX        32767  /* File's link count.        */
#define NAME_MAX        255    /* Bytes in a file name      */
#define NGROUPS_MAX     16     /* Number of simultaneous    */
                               /* supplementary group IDs   */
                               /* per process.              */
#define PATH_MAX        1024   /* Bytes in a pathname       */
#define PIPE_BUF        4096   /* Bytes that can be written */
                               /* atomically to a pipe.     */
#define SSIZE_MAX       INT_MAX /* Value that can be stored */
                                /* in object of type ssize_t.*/
#define STREAM_MAX      256    /* Open streams per process  */
#define TZNAME_MAX      50     /* bytes for time zone name  */

//#define S_IRUSR _S_IRUSR
//#define S_IWUSR _S_IWUSR
 typedef int sigset_t;

#define _SYS_NAMELEN    32

struct  utsname {
                        char    sysname[_SYS_NAMELEN];  /* Name of OS */
                                                        /* implementation */
                        char    nodename[_SYS_NAMELEN]; /* Name of this node */
                                                        /* in a network */
                        char    release[_SYS_NAMELEN];  /* Release level of */
                                                        /* OS implementation */
                        char    version[_SYS_NAMELEN];  /* Version level of */
                                                        /* OS implementation */
                        char    machine[_SYS_NAMELEN];  /* Hardware name */
};
extern int uname(struct utsname *name);



        #define O_ACCMODE       003     /* mask for file access modes */
        #define O_NONBLOCK      00004   /* non-blocking open */
        #define O_NOCTTY        00020   /* do not acquire a */



        #define S_IRUSR _S_IRUSR        /* read permission, owner */
        #define S_IRGRP 0000040         /* read permission, group */
        #define S_IROTH 0000004         /* read permission, other */
        #define S_IWUSR _S_IWUSR        /* write permission, owner */
        #define S_IWGRP 0000020         /* write permission, group */
        #define S_IWOTH 0000002         /* write permission, other */
        #define S_IXUSR _S_IXUSR        /* execute/search permission, */
                                        /* owner */
        #define S_IXGRP 0000010         /* execute/search permission, */
                                        /* group */
        #define S_IXOTH 0000001         /* execute/search permission, */
                                        /* other */
        #define S_IRWXU 0000700         /* read, write, execute */
                                        /* permissions, owner */
        #define S_IRWXG 0000070         /* read, write, execute */
                                        /* permissions, group */
        #define S_IRWXO 0000007         /* read, write, execute */
                                        /* permissions, other */

        #define S_ISBLK(mode)   (((mode) & (_S_IFMT)) == (_S_IFBLK))
        #define S_ISCHR(mode)   (((mode) & (_S_IFMT)) == (_S_IFCHR))
        #define S_ISDIR(mode)   (((mode) & (_S_IFMT)) == (_S_IFDIR))
        #define S_ISFIFO(mode)  (((mode) & (_S_IFMT)) == (_S_IFIFO))
        #define S_ISREG(mode)   (((mode) & (_S_IFMT)) == (_S_IFREG))



        #ifndef _TIME_T
                #define _TIME_T
                typedef long time_t;
        #endif

        struct utimbuf {
                time_t  actime;         /* Access time */
                time_t  modtime;        /* Modification time */
        };

                extern int utime(const char *path,
                        const struct utimbuf *times);



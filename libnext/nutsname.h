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
#include <sys/utsname.h>

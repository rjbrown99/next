#include <limits.h>

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


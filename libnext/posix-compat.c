//#if NS_TARGET_MAJOR < 4
//int __posix_compat__;
//#else
//#define _POSIX_SOURCE



#ifndef _POSIX_SOURCE
 #define _POSIX_JOB_CONTROL              1
 #define _POSIX_SAVED_IDS                1
 #define _POSIX_VERSION                  199009L
 #include "nlimits.h"
 #include "ntypes.h" 
 #include "nsignal.h"
#else
 #include <limits.h>
 #include <signal.h>
#endif
#include <sys/types.h>
#include <errno.h>
#include <sys/param.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef void (*handler_t) (int);



char *
getcwd(char *buf, size_t size) {
  extern char *getwd (char *);
  char *pathname;

  if (buf && !size) {
    errno = EINVAL;
    return (NULL);
  }
  
  if ((pathname = malloc(MAXPATHLEN + 1)) == NULL) return (NULL);

  if (!(getwd(pathname))) {
    free(pathname);
    return (NULL);
  }

  if (buf) {
    if (size < 1 + strlen(pathname)) {
      free(pathname);
      errno = ERANGE;
      return (NULL);
    }

    strcpy(buf,pathname);
    free(pathname);
    return (buf);

  } else return (pathname);
}
/* Set of currently blocked signals.  */
static volatile sigset_t blocked_set /* = 0 */;

/* Set of currently blocked and pending signals.  */
static volatile sig_atomic_t pending_array[NSIG] /* = { 0 } */;

/* Signal handler that is installed for blocked signals.  */
static void
blocked_handler (int sig)
{
  /* Reinstall the handler, in case the signal occurs multiple times
     while blocked.  There is an inherent race where an asynchronous
     signal in between when the kernel uninstalled the handler and
     when we reinstall it will trigger the default handler; oh
     well.  */
  signal (sig, blocked_handler);
  if (sig >= 0 && sig < NSIG)
    pending_array[sig] = 1;
}


int
sigpending (sigset_t *set)
{
  sigset_t pending = 0;
  int sig;

  for (sig = 0; sig < NSIG; sig++)
    if (pending_array[sig])
      pending |= 1U << sig;
  *set = pending;
  return 0;
}


int
sigdelset (sigset_t *set, int sig)
{
  if (sig >= 0 && sig < NSIG)
    {
      #ifdef SIGABRT_COMPAT
      if (sig == SIGABRT_COMPAT)
        sig = SIGABRT;
      #endif

      *set &= ~(1U << sig);
      return 0;
    }
  else
    {
      errno = EINVAL;
      return -1;
    }
}

/*
int
sigismember (const sigset_t *set, int sig)
{
  if (sig >= 0 && sig < NSIG)
    {
      #ifdef SIGABRT_COMPAT
      if (sig == SIGABRT_COMPAT)
        sig = SIGABRT;
      #endif

      return (*set >> sig) & 1;
    }
  else
    return 0;
}
*/
pid_t
setsid(void) {
  /* This ought'a work, but doesn't.  Can't find a way to call setpgrp
  without getting -1 returned.  Even getpgrp() returns -1.
  So far, return (0) seems good enough for BIND
  
  extern int setpgrp(int,int);

  if ((setpgrp(0,getpid())) == -1) return (-1);
  return (getpgrp());
  */
  return (0);
}

long
sysconf(int name) {
  static int v[10] = {
    ARG_MAX,
    CHILD_MAX,
    64,			/* ticks/sec */
    _POSIX_JOB_CONTROL,
    NGROUPS_MAX,
    OPEN_MAX,
    _POSIX_SAVED_IDS,
    STREAM_MAX,
    TZNAME_MAX,
    _POSIX_VERSION
    };

  if (name > 9 || name < 0) {
    errno = EINVAL;
    return (-1);
  }

  return (v[name]);
}

pid_t
waitpid(pid_t pid, int *stat_loc, int options) {
  extern pid_t wait4(int, union wait *, int, struct rusage *);

  return (wait4(((1+pid) ? pid : 0), (union wait *) stat_loc, options, NULL));
}

int
sigemptyset(sigset_t *set) {
  if (set == NULL) {
    errno = EINVAL;
    return (-1);
  }

  *set = 0;
  return (0);
}

int
sigfillset(sigset_t *set) {
  if (set == NULL) {
    errno = EINVAL;
    return (-1);
  }

  *set = ~(sigset_t)0;
  return (0);
}

int
sigaddset(sigset_t *set, int signo) {
  if (set == NULL || signo <= 0 || signo >= NSIG) {
    errno = EINVAL;
    return (-1);
  }

  *set |= sigmask(signo);
  return (0);
}

int
sigaction(int sig, const struct sigaction *act, struct sigaction *oact) {
  struct sigvec vec, ovec;

  if (sig <=0 || sig >= NSIG) {
    errno= EINVAL;
    return (-1);
  }

  if (act) {
    vec.sv_flags = act->sa_flags;
    vec.sv_handler = act->sa_handler;
    vec.sv_mask = act->sa_mask;
  }

  if (sigvec(sig, (act == NULL) ? NULL : &vec, &ovec)) return (-1);

  if (oact) {
    oact->sa_flags = ovec.sv_flags;
    oact->sa_handler = ovec.sv_handler;
    oact->sa_mask = ovec.sv_mask;
  }
  return (0);
}

int
sigprocmask(int how, const sigset_t *set, sigset_t *oset) {
  int old;

  old = sigblock(0);

  if (set) {
    switch(how) {
    case SIG_BLOCK:
      sigblock(*set);
      break;

    case SIG_UNBLOCK:
      sigsetmask(old & ~(*set));
      break;

    case SIG_SETMASK:
      sigsetmask(*set);
      break;

    default:
      errno = EINVAL;
      return (-1);
    }
  }

    if (oset) *oset = old;
    return (0);
}


//#endif

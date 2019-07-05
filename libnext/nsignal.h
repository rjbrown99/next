#include <signal.h> 

       typedef int sigset_t;

        struct sigaction {
                void            (*sa_handler)();
                sigset_t        sa_mask;
                int             sa_flags;
        };

        #define SIG_BLOCK       00
        #define SIG_UNBLOCK     01
        #define SIG_SETMASK     02

        #define SA_NOCLDSTOP    04

                extern int kill(pid_t pid, int sig);
                extern int sigaction(int sig, \
                                     const struct sigaction *act, \
                                     struct sigaction *oact);
                extern int sigaddset(sigset_t *set, int signo);
                extern int sigdelset(sigset_t *set, int signo);
                extern int sigemptyset(sigset_t *set);
                extern int sigfillset(sigset_t *set);
                extern int sigismember(const sigset_t *set, int signo);
                extern int sigpending(sigset_t *set);
                extern int sigprocmask(int how, const sigset_t *set, \
                                       sigset_t *oset);
                extern int sigsuspend(const sigset_t *sigmask);


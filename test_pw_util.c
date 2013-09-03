#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>

#define _OPEN_SYS
#include <pwd.h>
#include <libutil.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int pw_equal(const struct passwd *_pw1, const struct passwd *_pw2);
int pw_copy(int ffd, int tfd, const struct passwd *pw, struct passwd *old_pw);
//int putpwent(const struct passwd *p, FILE *stream);

int main(int argc, char *argv[]) {
  struct passwd *p11;
  struct passwd p22;
  const struct passwd *ptemp;
  char user[]="arielb";

  if ((p11 = getpwnam(user)) == NULL)
    perror("getpw() error");
  else {
    printf("getpw() returned the following info for user %s:\n",
           user);

    p22.pw_name = "test1";
    p22.pw_uid = (int)501;
    p22.pw_gid = (int)512;
    p22.pw_dir = "/home/test1";
    p22.pw_shell = "/bin/bash";
    p22.pw_class = "class";
    p22.pw_gecos = "Test One";
    p22.pw_dir = "/home/test1";

    printf("  pw_name  : %s\n",       p11->pw_name);
    printf("  pw_uid   : %d\n", (int) p11->pw_uid);
    printf("  pw_gid   : %d\n", (int) p11->pw_gid);
    printf("  pw_dir   : %s\n",       p11->pw_dir);
    printf("  pw_class : %s\n",       p11->pw_shell);
    printf("  pw_change : %ld\n",     (long int)p11->pw_change);
    printf("  pw_expire : %ld\n",     (long int)p11->pw_expire);
    printf("  pw_gecos : %s\n",       p11->pw_gecos);
    printf("  pw_dir : %s\n",       p11->pw_dir);

    printf("\n\n");
    printf("  pw_name  : %s\n",       p22.pw_name);
    printf("  pw_uid   : %d\n", (int) p22.pw_uid);
    printf("  pw_gid   : %d\n", (int) p22.pw_gid);
    printf("  pw_dir   : %s\n",       p22.pw_dir);
    printf("  pw_class : %s\n",       p22.pw_shell);
    printf("  pw_change : %ld\n",     (long int)p22.pw_change);
    printf("  pw_expire : %ld\n",     (long int)p22.pw_expire);
    printf("  pw_gecos : %s\n",       p22.pw_gecos);
    printf("  pw_dir : %s\n",       p22.pw_dir);

    ptemp = &p22;
    if (!pw_equal(p11, ptemp))
    {
       int err = 0;
       int ffd, tfd;

       ffd = open("/etc/passwd", O_RDWR);
       tfd = open("/home/arielb/.passwd", O_RDWR);

       if (ffd < 0 )
       {
          err = errno;
          printf("ERROR [%d] - %s\n",err, strerror(err));
       }else{
          int c;
           ptemp = &p22;
           c = pw_copy(ffd, tfd, ptemp, NULL);
           close(ffd);
           close(tfd);
       }
    } else 
    {
        printf("user already exists");
    }
  }
  return 0;
}

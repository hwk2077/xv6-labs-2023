#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i, p, n;
  int pl[2], pr[2];
  int first;
  if(argc > 1) {
    fprintf(2, "Usage: prime\n");
    exit(1);
  }
  pipe(pl);
  if (fork() != 0) {
    close(pl[0]);
    for (i = 2; i <= 35; i++) {
      write(pl[1], &i, sizeof(i));
    }
    close(pl[1]);
  } else {
    close(pl[1]);
    p = 0;
    first = 1;
    while(read(pl[0], &n, sizeof(n)) != 0) {
      if (first) {
        pipe(pr);
        if (fork() != 0) {
          close(pr[0]);
          p = n;
          first = 0;
          printf("prime %d\n", p);
        } else {
          close(pr[1]);
          pl[0] = pr[0];
        }
      } else {
        if (n % p != 0) {
          write(pr[1], &n, sizeof(n));
        }
      }
    }
    close(pl[0]);
    close(pr[1]);
  }
  wait(0);
  exit(0);
}

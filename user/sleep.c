#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int t;

  if(argc != 2){
    fprintf(2, "Usage: sleep...\n");
    exit(1);
  }
  
  t = atoi(argv[1]);
  if (sleep(t) < 0) {
    fprintf(2, "sleep: failed to sleep %d\n ticks", t);
  }

  exit(0);
}

#include "kernel/types.h"
#include "user/user.h"

char buf[17];

void
sleep_u(int time)
{
  if(time <= 0) {
    fprintf(2,"sleep: please input a positive number!\n");
    exit(1);
  }
  fprintf(1,"sleep: I will sleep %s ticks, zzz\n",time);
  sleep(time);
  return;
}

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2,"sleep: please input how long you want to sleep!\n");
    exit(1);
  }else if( argc > 2) {
    fprintf(2,"sleep: there're two inputs, expect one!\n");
    exit(1);
  }

  int time = atoi(argv[1]);

  sleep_u(time);

  exit(0);
}

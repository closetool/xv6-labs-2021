#include <kernel/types.h>
#include <user/user.h>

char* name = "primes";

void prime(int *fds,int* arr, int n);

int main(){
  int fds[2];
  if(pipe(fds) < 0){
    fprintf(2,"%s: create pipe failed!\n",name);
    exit(1);
  }
  int buf[34];
  for(int i = 0; i < 34;i++) {
    buf[i] = i+2;
  }
  prime(fds,buf,34);
  exit(0);
}

void prime(int *fds,int* arr, int n) {
  printf("prime\n");
  int pid = fork();
  if(pid < 0) {
    fprintf(2,"%s: could not create child process!\n",name);
    exit(1);
  }else if(pid > 0) {
    int x = arr[0];
    printf("%d\n",x);
    for(int i = 1;i<n;i++) {
      if(arr[i]%x==0){
        continue;
      }
      printf("%d: write %d\n",getpid(),arr[i]);
      write(fds[1],&arr[i],sizeof(int));
    }
    wait(0);
  }else{
    int buf[n];
    int x = 0;
    int num = 0;
    for(int i = 0;i<n;i++) {
      if(read(fds[0],&x,sizeof(4)) > 0) {
        buf[i] = x;
        printf("%d: read %d\n",getpid(),buf[i]);
        num++;
      }else{
        break;
      }
    }
    close(fds[1]);
    close(fds[0]);
    if(pipe(fds) < 0){
      fprintf(2,"%s: create pipe failed!\n",name);
      exit(1);
    }
    prime(fds,buf,num);
  }
  exit(0);
}

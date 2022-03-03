#include <kernel/types.h>
#include <user/user.h>

int getpid_u();
void read_from_pipe_and_print(int fd);
void write_to_pipe(int fd,char* msg);
void close_fd(int fd);

int main(){

  int fd1[2],fd2[2];

  if(pipe(fd1) < 0 || pipe(fd2) < 0) {
    fprintf(2,"pingpong: create pipe failed!\n");
    exit(1);
  }

  int pid = fork();
  if(pid < 0) {
    fprintf(2,"pingpong: create child process failed!\n");
    exit(1);
  }else if(pid > 0) {
    char* data = "ping";
    write_to_pipe(fd1[1],data);
    close_fd(fd1[1]);
    read_from_pipe_and_print(fd2[0]);
    close_fd(fd2[0]);
  }else{
    char* data = "pong";
    read_from_pipe_and_print(fd1[0]);
    close_fd(fd1[0]);
    write_to_pipe(fd2[1],data); 
    close_fd(fd2[1]);
  }
  exit(0);
}

void write_to_pipe(int fd,char* msg) {
    if(write(fd,msg,strlen(msg)) < 0) {
      fprintf(2,"pingpong: write to pipe failed!\n");
      exit(1);
    }
}

void read_from_pipe_and_print(int fd) {
    int n=10;
    char data[n];
    if((n = read(fd,data,n)) < 0)  {
      fprintf(2,"pingpong: read from pipe failed!\n");
      exit(1);
    }
    fprintf(1,"%d: received ",getpid_u());
    write(1,data,n);
    fprintf(1,"\n");
}

void close_fd(int fd) {
    if(close(fd) < 0) {
      fprintf(2,"pingpong: close pipe failed!\n");
      exit(0);
    }
}

int getpid_u() {
  int pid = getpid();
  if(pid<0) {
    fprintf(2,"pingpong: failed to get pid!\n");
    exit(1);
  }
  return pid;
}

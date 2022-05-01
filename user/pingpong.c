#include <stdint.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int parent_pipe[2];
  int child_pipe[2];

  char *pingpong = "a";

  if (pipe(parent_pipe) < 0) {
    fprintf(2, "pipe\n");
    exit(1);
  }
  if (pipe(child_pipe) < 0) {
    fprintf(2, "pipe\n");
    exit(1);
  }

  int rc = fork();
  if (rc < 0) {
    fprintf(2, "fork failed\n");
    exit(1);
  } else if (rc > 0) {
    char parent_buffer[1024];

    close(parent_pipe[0]);
    write(parent_pipe[1], pingpong, strlen(pingpong));

    wait(0);

    close(child_pipe[1]);
    read(child_pipe[0], parent_buffer, strlen(pingpong));
    close(child_pipe[0]);

    int ppid = getpid();
    printf("%d: received pong\n", ppid);
  } else {
    char child_buffer[1024];

    close(parent_pipe[1]);

    read(parent_pipe[0], child_buffer, strlen(pingpong));

    close(parent_pipe[0]);
    close(child_pipe[0]);

    int child_pid = getpid();
    printf("%d: received ping\n", child_pid);

    write(child_pipe[1], pingpong, strlen(pingpong));

    close(child_pipe[1]);
  }

  exit(0);
}

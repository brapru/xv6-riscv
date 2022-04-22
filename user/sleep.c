#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define ERR 0
#define OK 1

int is_valid_time(char number[]) {
  if (number[0] == '-') {
    return ERR;
  }

  for (int i = 0; number[i] != 0; i++) {
    if (number[i] > '9' || number[i] < '0')
      return ERR;
  }

  return OK;
}

int main(int argc, char *argv[]) {
  int time;

  if (argc != 2) {
    fprintf(2, "usage: sleep [ticks]\n");
    exit(1);
  }

  if (!is_valid_time(argv[1])) {
    fprintf(2, "invalid sleep input: must be valid integer\n");
    exit(1);
  }

  time = atoi(argv[1]);
  sleep(time);

  exit(0);
}

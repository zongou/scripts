#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

#define MAX 100000
#define SIZE 100
#define NUMS_TO_GENERATE 10

int main() {
  unsigned int tmp;

  getrandom(&tmp, sizeof(unsigned int), GRND_NONBLOCK) == -1
      ? perror("getrandom")
      : "";
  printf("%u\n", tmp);

  exit(EXIT_SUCCESS);
}
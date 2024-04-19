#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <time.h>

#define MAX 100000
#define SIZE 100
#define NUMS_TO_GENERATE 10

int main() {
  srandom(time(NULL));
  for (int i = 0; i < NUMS_TO_GENERATE; i++) {
    printf("%ld\n", random() / MAX);
  }
  exit(EXIT_SUCCESS);
}
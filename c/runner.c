#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void call_system(int argc, char *argv[]) {
  char *runner = "zig run -lc -static";
  char result[1000];

  strcpy(result, runner);
  strcat(result, " ");

  for (int i = 1; i < argc; i++) {
    strcat(result, argv[i]);
    strcat(result, " ");
  }

  printf("run: %s\n", result);
  system(result);
}

// void exec_demo() {
//   char *prog = "/bin/busybox";
//   char *arg1 = "printenv";
//   // execl(prog, "uname", arg1, NULL);
//   // execlp(prog, "uname", arg1, NULL);

//   char *envp[] = {NULL};
//   // execle(prog, "uname", arg1, NULL, envp);

//   char *args[] = {prog, arg1, NULL};
//   // execv(prog, args);
//   // execvp(prog, args);
//   execvpe(prog, args, envp);

//   // execve(prog, args, envp);
//   fprintf(stderr, "failed to run %s\n", prog);
// }

// int main(int argc, char *argv[]) {
//   if (argc >= 2) {
//     // call_system(argc, argv);
//     call_exec(argc, argv);
//   } else {
//     fprintf(stderr, "%s\n", "No arguments");
//   }

//   return 0;
// }

extern char **environ;

int print_env_list1() {
  char **envir = environ;

  while (*envir) {
    fprintf(stdout, "%s\n", *envir);
    envir++;
  }
  return 0;
}

int print_env_list2(int argc, char *argv[], char *env[]) {
  for (int i = 0; env[index]; i++) {
    printf("env[%d]: %s\n", index, env[index]);
  }
  return 0;
}

int main() {
  int count = 0;
  while (environ[count]) {
    puts(environ[count]);
    ++count;
  }
  printf("count=%d\n", count);

  char *strList[] = {"aa", "bb", "cc", NULL};
  count = 0;
  while (strList[count]) {
    puts(strList[count]);
    count++;
  }

  char *str = "Hello wrold!\n";
  count = 0;
  while (str[count]) {
    putchar(str[count]);
    count++;
  }

  for (int i = 0; str[i]; i++) {
    putchar(str[i]);
  }
}
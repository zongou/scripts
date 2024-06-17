#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *concatenate_strings(const char *str1, const char *str2) {
  // 计算两个字符串的总长度
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int total_len = len1 + len2 + 1; // +1 为了包含字符串结尾的 '\0'

  // 动态分配足够大小的内存来存储拼接后的字符串
  char *result = malloc(total_len * sizeof(char));
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  // 拼接字符串
  strncpy(result, str1, len1);
  strncpy(result + len1, str2, len2 + 1); // len2 + 1 为了包含结尾的 '\0'

  return result;
}

int command_login(char *rootfs) {
  FILE *pipe = popen("command -v proot", "r");
  if (pipe) {
    char buffer[1024];
    fgets(buffer, sizeof(buffer), pipe);

    if (pclose(pipe) == 0) {
      char prog[strlen(buffer)];
      strlcpy(prog, buffer, sizeof(prog));
      // printf("size=%lu\n", sizeof(prog));
      // printf("final=[%s]\n", prog);

      char *args[] = {prog,
                      concatenate_strings("--rootfs=", rootfs),
                      "--cwd=/root",
                      "--kill-on-exit",
                      "--root-id",
                      "--link2symlink",
                      "--bind=/dev",
                      "--bind=/dev/urandom:/dev/random",
                      "--bind=/proc",
                      "--bind=/proc/self/fd:/dev/fd",
                      "--bind=/proc/self/fd/0:/dev/stdin",
                      "--bind=/proc/self/fd/1:/dev/stdout",
                      "--bind=/proc/self/fd/2:/dev/stderr",
                      "--bind=/sys",
                      NULL};

      setenv("LD_PRELOAD", "", 1);
      char *tmpdir = getenv("TMPDIR");
      setenv("PROOT_TMP_DIR", tmpdir, 1);
      execv(prog, args);
    }
  }
}

// int main(int argc, char *argv[]) {
//   // command_login(NULL);
//   char *rootfs = "/root/alpine";
//   char *arg_rootfs = "--rootfs=";

//   arg_rootfs = strcpy(arg_rootfs, rootfs);

//   // strcpy("--rootfs=", rootfs);
//   printf("%s\n", arg_rootfs);
//   return 0;
// }

int parse_args(int argc, char *argv[]) {
  printf("[%s]\n", argv[1]);
  return 0;
}

int main(int argc, char *argv[]) {
  // printf("[%s]\n", concatenate_strings("--rootfs=", "/root/alpine"));
  command_login(argv[1]);

  return 0;
}

// #include <stdio.h>
// #in'clude <string.h>

// Function to parse command line arguments for a specific flag
// void parseArgument(int argc, char *argv[], const char *flag, char **value) {
//   // Loop through all arguments
//   for (int i = 1; i < argc; ++i) {
//     // Check if the current argument is the flag we're looking for
//     if (strncmp(argv[i], flag, strlen(flag)) == 0 &&
//         argv[i][strlen(flag)] == '=') {
//       // Found the flag, set the value pointer to the content after '='
//       *value = argv[i] + strlen(flag) + 1;
//       return; // Exit the function after finding the first occurrence
//     }
//   }

//   // If the flag wasn't found, set the value pointer to NULL
//   *value = NULL;
// }

// int main(int argc, char *argv[]) {
//   char *inputFile = NULL;

//   // Example usage of parseArgument function to find --input=value pattern
//   parseArgument(argc, argv, "--input=", &inputFile);

//   if (inputFile != NULL) {
//     printf("Input file specified: %s\n", inputFile);
//   } else {
//     printf("No input file specified.\n");
//   }

//   return 0;
// }

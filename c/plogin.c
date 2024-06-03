#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
                      "--rootfs=/data/data/my.term/files/home/alpine_dev",
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

int main(int argc, char *argv[]) {
  // command_login(NULL);
  char *rootfs = "/root/alpine";
  char *arg_rootfs = "--rootfs=";

  arg_rootfs = strcpy(arg_rootfs, rootfs);

  // strcpy("--rootfs=", rootfs);
  printf("%s\n", arg_rootfs);
  return 0;
}

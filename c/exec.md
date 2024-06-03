SYNOPSIS

exec()

```c
#include <unistd.h>

// POSIX.1-2001.
extern char **environ;
int execl(const char *pathname, const char *arg, ... /*, (char *) NULL */);
int execlp(const char *file, const char *arg, ... /*, (char *) NULL */);
int execle(const char *pathname, const char *arg, ... /*, (char *) NULL, char *const envp[] */);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]);
// glibc 2.11.
int execvpe(const char *file, char *const argv[], char *const envp[]);
```

execve()

```c
#include <unistd.h>

int execve(const char *pathname, char *const _Nullable argv[],
char *const _Nullable envp[]);
```

| meaning  | letter |
| -------- | ------ |
| pathname |        |
| filename | p      |
| fd       | f      |
| arg list | l      |
| argv[]   | v      |
| environ  |        |
| envp[]   | e      |

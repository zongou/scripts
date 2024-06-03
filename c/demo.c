#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef VERSION
#define VERSION "0.0.0"
#endif

#ifndef PROG_NAME
#define PROG_NAME "demo"
#endif

struct {
  int help_flag;
  int version_flag;
} options;

void show_version() {
  fprintf(stderr, "\
%s %s\n\
\n\
Author: zongou\n\
2024, ZheJiang China.\n\
",
          PROG_NAME, VERSION);
}

void show_help() {
  fprintf(stderr, "\
My script.\n\
Usage:\n\
  %s [options]\n\
  Options:\n\
    -h, --help                 \tshow this help.\n\
    -v, --version              \tshow version.\n\
",
          PROG_NAME);
}

int main(int argc, char **argv) {
  if (argc > 1) {

    int c;
    while (1) {
      static struct option long_options[] = {/* These options set a flag. */
                                             {"help", no_argument, 0, 'h'},
                                             {"version", no_argument, 0, 'v'},
                                             {0, 0, 0, 0}};
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long(argc, argv, "hv", long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c) {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
          break;
        printf("option %s", long_options[option_index].name);
        if (optarg)
          printf(" with arg %s", optarg);
        printf("\n");
        break;

      case 'h':
        options.help_flag = 1;
        break;

      case 'v':
        options.version_flag = 1;
        break;

      case '?':
        /* getopt_long already printed an error message. */
        break;

      default:
        abort();
      }
    }

    if (options.help_flag) {
      show_help();
    } else if (options.version_flag) {
      show_version();
    }
  } else {
    show_help();
  }

  exit(0);
}

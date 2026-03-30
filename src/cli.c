#include <string.h>

#include "cli.h"

CLIArgs cli_parseArgs(int argc, char **argv) {
  CLIArgs args = {0};
  if (argc == 1)
    return args;

  if (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "a") == 0) {
    args.sub_command = CLI_ADD;
  } else if (strcmp(argv[1], "remove") == 0 || strcmp(argv[1], "r") == 0) {
    args.sub_command = CLI_REMOVE;
  } else {
    args.sub_command = CLI_UNKNOWN;
    args.value = argv[1];
  }

  return args;
}

void cli_freeArgs(CLIArgs args) {}

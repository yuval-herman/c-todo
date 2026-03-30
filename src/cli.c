#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"

// Value is used directly, if you intend to change the string later, call strdup on
// it first
static void cli_addValue(CLIArgs *args, char* value) {
  unsigned int new_values_amount = args->values_amount + 1;
  args->values = realloc(args->values, sizeof(args->values[0]) * new_values_amount);
  args->values[args->values_amount] = value;
  args->values_amount = new_values_amount;
}

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
    args.values = &argv[1];
    args.values_amount = 1;
    args.error_code = CLI_ERROR_UNKNOWN_SUBCOMMAND;
  }

  return args;
}

void cli_printError(CLIArgs args) {
  switch (args.error_code) {
  case CLI_ERROR_OKAY:
    fprintf(stderr, "No error happened, why did you call me? (・・?)\n");
    break;
  case CLI_ERROR_UNKNOWN_SUBCOMMAND:
    fprintf(stderr, "Received unknown sub-command: [%s]\n", args.values[0]);
    break;

  default:
    fprintf(stderr, "Unknown error code: %d\n", args.error_code);
  }
}

void cli_freeArgs(CLIArgs args) {}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../nob.h"
#include "cli.h"

static CLIError last_error_code = CLI_ERROR_OKAY;
static char *last_error_value = NULL;

// Value is used directly, if you intend to change the string later, call strdup
// on it first
static void cli_addValue(CLIArgs *args, char *value) {
  unsigned int new_values_amount = args->values_amount + 1;
  args->values =
      realloc(args->values, sizeof(args->values[0]) * new_values_amount);
  args->values[args->values_amount] = value;
  args->values_amount = new_values_amount;
}

static void cli_addId(CLIArgs *args, unsigned int id) {
  unsigned int new_ids_amount = args->todo_ids_amount + 1;
  args->todo_ids =
      realloc(args->todo_ids, sizeof(args->todo_ids[0]) * new_ids_amount);
  args->todo_ids[args->todo_ids_amount] = id;
  args->todo_ids_amount = new_ids_amount;
}

// static cli_parseOptions() TBD

static CLIArgs cli_parseAdd(int argc, char **argv) {
  CLIArgs args = {0};

  args.sub_command = CLI_ADD;

  if (argc < 3) {
    last_error_code = args.error_code = CLI_ERROR_EXPECTED_VALUE;
    return args;
  }
  // No options and one value
  else if (argc == 3) {
    cli_addValue(&args, strdup(argv[2]));
    return args;
  }

  String_Builder sb = {0};

  // TODO add option parsing
  for (int i = 2; i < argc; ++i) {
    sb_append_cstr(&sb, argv[i]);
    sb_append(&sb, ' ');
  }
  da_last(&sb) = '\0';

  cli_addValue(&args, sb.items);

  return args;
}

static CLIArgs cli_parseRemove(int argc, char **argv) {
  CLIArgs args = {0};
  // Here we will place parsed ids before passing them to `cli_addId`
  int id;

  args.sub_command = CLI_REMOVE;

  if (argc < 3) {
    last_error_code = args.error_code = CLI_ERROR_EXPECTED_VALUE;
    return args;
  }

  // TODO add option parsing
  for (int i = 2; i < argc; ++i) {
    int res = sscanf(argv[i], "%4d", &id);
    if (res != 1 || id < 0) {
      last_error_code = args.error_code = CLI_ERROR_INVALID_ID;
      free(last_error_value);
      last_error_value = strdup(argv[i]);
      return args;
    }
    cli_addId(&args, id);
  }

  return args;
}

CLIArgs cli_parseArgs(int argc, char **argv) {
  CLIArgs args = {0};
  if (argc == 1)
    return args;

  if (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "a") == 0) {
    args = cli_parseAdd(argc, argv);
  } else if (strcmp(argv[1], "remove") == 0 || strcmp(argv[1], "r") == 0) {
    args = cli_parseRemove(argc, argv);
  } else {
    args.sub_command = CLI_UNKNOWN;
    free(last_error_value);
    last_error_value = strdup(argv[1]);
    last_error_code = args.error_code = CLI_ERROR_UNKNOWN_SUBCOMMAND;
  }

  return args;
}

void cli_printLastError() {
  switch (last_error_code) {
  case CLI_ERROR_OKAY:
    fprintf(stderr, "No error happened, why did you call me? (・・?)\n");
    break;
  case CLI_ERROR_UNKNOWN_SUBCOMMAND:
    fprintf(stderr, "Received unknown sub-command: [%s]\n", last_error_value);
    break;
  case CLI_ERROR_OPTIONS_IN_VALUE:
    fprintf(stderr, "Options (e.g. -flag) were given in the middle of the "
                    "argument to the sub-command. Options should appear either "
                    "before or after the main value\n");
    break;
  case CLI_ERROR_INVALID_ID:
    fprintf(stderr,
            "An invalid todo id was given: [%s].\nA valid todo id is a "
            "positive integer\n",
            last_error_value);
    break;
  case CLI_ERROR_EXPECTED_VALUE:
    fprintf(stderr,
            "The requested operation requires a value but none was given\n");
    break;
  default:
    fprintf(stderr, "Unknown error code: %d\n", last_error_code);
  }
}

void cli_freeArgs(CLIArgs args) {
  for (unsigned int i = 0; i < args.values_amount; ++i) {
    free(args.values[i]);
  }
  free(args.values);
  free(args.todo_ids);
  free(last_error_value);
}

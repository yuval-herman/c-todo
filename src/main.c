#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "manager.h"
#include "parser.h"
#include "types.h"

int main(int argc, char **argv) {
  CLIArgs args = cli_parseArgs(argc, argv);
  if (args.error_code != CLI_ERROR_OKAY) {
    cli_printError(args);
    exit(args.error_code);
  }

  switch (args.sub_command) {
  case CLI_NONE:
    fprintf(stderr, "No command provided\n");
    exit(-1);
  case CLI_ADD:
    printf("Added new todo [%s]\n", args.values[0]);
    break;
  case CLI_REMOVE:
    printf("Removed todo\n");
    break;
  case CLI_UNKNOWN: // Unknown should be handled above in the error handling code
  default:
    assert(0 && "Reached impossible sub-command");
  }

  cli_freeArgs(args);
  // TodoItem todo = parseTodoString(argv[1]);
  // printTodoItem(todo);
  // freeTodo(todo);
  return 0;
}

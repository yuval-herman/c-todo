#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "manager.h"
#include "parser.h"
#include "types.h"

int main(int argc, char **argv) {
  CLIArgs args = cli_parseArgs(argc, argv);

  switch (args.sub_command) {
  case CLI_NONE:
    fprintf(stderr, "No command provided\n");
    exit(1);
  case CLI_UNKNOWN:
    fprintf(stderr, "An unknown command was provided: [%s]\n", args.value);
    exit(1);
  case CLI_ADD:
    printf("Added new todo\n");
    break;
  case CLI_REMOVE:
    printf("Removed todo\n");
    break;
  }

  cli_freeArgs(args);
  // TodoItem todo = parseTodoString(argv[1]);
  // printTodoItem(todo);
  // freeTodo(todo);
  return 0;
}

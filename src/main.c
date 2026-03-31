#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"
#include "cli.h"
#include "manager.h"
#include "types.h"

int main(int argc, char **argv) {
  CLIArgs args = cli_parseArgs(argc, argv);
  if (args.error_code != CLI_ERROR_OKAY) {
    cli_printLastError();
    int error_code = args.error_code;
    cli_freeArgs(args);
    exit(error_code);
  }

  TodoDA todos = manager_readTodoFile("test.todo");
  da_foreach(TodoItem, todo, &todos) {
    manager_freeTodo(*todo);
  }
  da_free(todos);

  switch (args.sub_command) {
  case CLI_NONE:
    fprintf(stderr, "No command provided\n");
    exit(-1);
  case CLI_ADD: {
    TodoItem todo = manager_todoFromString(args.values[0]);
    printf("Added new todo\n");
    manager_printTodoItem(todo);
    manager_freeTodo(todo);
    break;
  }
  case CLI_REMOVE:
    if (args.todo_ids_amount == 1) {
      printf("Removed todo %u\n", args.todo_ids[0]);
    } else {
      printf("Removed todos ");
      for (unsigned int i = 0; i < args.todo_ids_amount - 1; ++i) {
        printf("%u, ", args.todo_ids[i]);
      }
      printf("%u\n", args.todo_ids[args.todo_ids_amount - 1]);
    }
    break;
  case CLI_UNKNOWN: // Unknown should be handled above in the error handling
                    // code
  default:
    assert(0 && "Reached impossible sub-command");
  }

  cli_freeArgs(args);
  manager_destroy();
  // TodoItem todo = parseTodoString(argv[1]);
  // printTodoItem(todo);
  // freeTodo(todo);
  return 0;
}

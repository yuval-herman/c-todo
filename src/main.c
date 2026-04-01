#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"
#include "cli.h"
#include "manager.h"
#include "types.h"

int main(int argc, char **argv) {
  CLIArgs args = {0};
  bool ret = cli_parseArgs(&args, argc, argv);
  if (!ret) {
    cli_freeArgs(args);
    exit(1);
  }

  switch (args.sub_command) {
  case CLI_NONE:
    fprintf(stderr, "No command provided\n");
    exit(-1);
  case CLI_ADD: {
    TodoItem todo = {0};
    ret = manager_todoFromString(&todo, args.values[0]);
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
  case CLI_LIST: {
    TodoDA todos = {0};
    ret = manager_readTodoFile(&todos, "test.todo");
    if (!ret)
      return 1;
    da_foreach(TodoItem, todo, &todos) {
      manager_printTodoItem(*todo);
      manager_freeTodo(*todo);
    }
    da_free(todos);
  } break;
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

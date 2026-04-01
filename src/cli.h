#ifndef CLI_H
#define CLI_H

// invocation structure:
// td <sub-command> <options> <values> <options>
//
//
// ////// add, a
// td add <todo-txt>
// td a <todo-txt>
//
// `add` should return a single string in the `values` field.
// If the user did not quote the string and multiple values were received,
// `add` should concatenate them into a single string.
//
// If no value is provided, an error is returned.
// If options were inserted in the middle of the <todo-txt> an error should be
// returned.
//
// ////// remove, r
// td remove <td-id...>
// td r <td-id...>
//
// `remove` should return an id array in the `todo_ids` field.
// Each <td-id> is a four digit number, if a larger number is provided, it is
// truncated at the fourth digit.
//
// If no value is provided, an error is returned.
// If options were inserted in the middle of the <todo-id...> an error should
// be returned. If non numeric ids were given, an error should be returned.
//

#include <stdbool.h>
typedef enum {
  CLI_NONE = 0, // When no sub-command was provided
  CLI_UNKNOWN,  // When an unknown sub-command was provided
  CLI_ADD,
  CLI_REMOVE,
  CLI_LIST,
} CLISubcommand;

typedef struct {
  CLISubcommand sub_command;
  char **values;
  unsigned int values_amount;
  unsigned int *todo_ids; // There are multiple sub-commands that operate on a todo id.
                 // If this field is redundant for this particular sub-command,
                 // it should therefore be ignored, and no assumptions on the
                 // value should be made
  unsigned int todo_ids_amount;
} CLIArgs;

// Allocates memory, call `freeArgs` when done with the args
bool cli_parseArgs(CLIArgs *args, int argc, char **argv);

// Frees the `CLIArgs` struct
void cli_freeArgs(CLIArgs args);

#endif // CLI_H

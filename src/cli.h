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
// td remove <td-ids...>
// td r <td-ids...>
//
// `remove` should return an id array in the `todo_ids` field.
//
// If no value is provided, an error is returned.
// If options were inserted in the middle of the <todo-ids...> an error should
// be returned. If non numeric ids were given, an error should be returned.
//

typedef enum {
  CLI_NONE = 0, // When no sub-command was provided
  CLI_UNKNOWN,  // When an unknown sub-command was provided
  CLI_ADD,
  CLI_REMOVE,
} CLISubcommand;

typedef enum {
  CLI_ERROR_OKAY = 0,           // No error
  CLI_ERROR_UNKNOWN_SUBCOMMAND, // Returned for an unknown subcommand
  CLI_ERROR_OPTIONS_IN_VALUE, // Returned when options were given in the middle
                              // of a value string
  CLI_ERROR_INVALID_ID,       // Returned when a todo id is invalid
  CLI_ERROR_EXPECTED_VALUE, // Returned when a sub-command had a required value
                            // argument but none was given
} CLIError;

typedef struct {
  CLISubcommand sub_command;
  char **values;
  unsigned int values_amount;
  int *todo_ids; // There are multiple sub-commands that operate on a todo id.
                 // If this field is redundant for this particular sub-command,
                 // it should therefore be ignored, and no assumptions on the
                 // value should be made
  unsigned int todo_ids_amount;
  CLIError error_code; // zero for no error
} CLIArgs;

// Allocates memory, call `freeArgs` when done with the args
CLIArgs cli_parseArgs(int argc, char **argv);

// Print an error for the given error code
void cli_printError(CLIArgs args);

// Frees the `CLIArgs` struct
void cli_freeArgs(CLIArgs args);

#endif // CLI_H

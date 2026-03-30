#ifndef CLI_H
#define CLI_H

// td add <todo-txt>
// td a <todo-txt>
// td remove <td-id>
// td r <td-id>

typedef enum {
  CLI_NONE = 0, // When no sub-command was provided
  CLI_UNKNOWN, // When an unknown sub-command was provided
  CLI_ADD,
  CLI_REMOVE,
} CLISubcommand;

typedef struct {
  CLISubcommand sub_command;
  char *value;
} CLIArgs;

// Allocates memory, call `freeArgs` when done with the args
CLIArgs cli_parseArgs(int argc, char **argv);

// Frees the `CLIArgs` struct
void cli_freeArgs(CLIArgs args);

#endif // CLI_H

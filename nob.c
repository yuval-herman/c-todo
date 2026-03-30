#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Cmd cmd = {0};
  nob_cc(&cmd);
  nob_cc_flags(&cmd);
  nob_cc_output(&cmd, "td");
  nob_cc_inputs(&cmd, "src/cli.c", "src/main.c", "src/parser.c",
                "src/manager.c");
  if (!cmd_run(&cmd))
    return 1;
  return 0;
}

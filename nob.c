#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc"); // We only support gcc
  nob_cc_flags(&cmd);
  nob_cmd_append(&cmd, "-g");
  nob_cmd_append(&cmd, "-Werror=switch-enum");
  nob_cc_output(&cmd, "td");
  nob_cc_inputs(&cmd, "src/cli.c", "src/main.c", "src/parser.c",
                "src/manager.c");
  if (!cmd_run(&cmd))
    return 1;
  return 0;
}

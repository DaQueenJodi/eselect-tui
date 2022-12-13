#include "eselect.h"
#include "tui.h"
#include "util.h"
#include <string.h>

List *get_eselect_modules(void) {
  List *l = new_list();

  String *cmd =
      run_shell_command("eselect --brief modules list | awk '{print $1}'");

  char *token = strtok(cmd->buff, "\n");

  int counter = 0;

  while (token != NULL) {
    if (counter > 2) { // skip first few since theyre builtins and dont apply to
                       // this program

      char *token_copy = strdup(token);
      append_list(l, token_copy);
    } else {
      counter += 1;
    }
    token = strtok(NULL, "\n");
  }
  free_string(cmd);

  return l;
}

OptionList *get_eselect_options(char *module) {
  OptionList *ol = new_option_list();

  char *cmd_str =
      malloc((strlen(module) + 13) * sizeof(char) +
             1); // allocate exactly enough bytes + 1 for null terminator

  sprintf(cmd_str, "eselect %s list", module);

  String *cmd = run_shell_command(cmd_str);

  free(cmd_str);

  char *token = strtok(cmd->buff, "\n");

  int counter = 0;

  while (token != NULL) {
    if (counter > 0) {
      append_option_list(ol, token, false);
    } else
      (counter = 1);
    token = strtok(NULL, "\n");
  }

  free_string(cmd);

  return ol;
}

int eselect_toggle(char *module, size_t num) {
  char *cmd_str =
      malloc(strlen(module) + 30 + 4 // leave 4 bytes for number just in case
             + 1); // allocate exactly enough bytes + 1 for null terminator

  sprintf(cmd_str, "eselect %s set %lx &>error", module, num);
  int err = system(cmd_str);
	puts(cmd_str);
	free(cmd_str);
	return err;
}

#include "tui.h"
#include <stdlib.h>

List *get_eselect_modules(void);
OptionList *get_eselect_options(char *module);
int eselect_toggle(char *module, size_t num);

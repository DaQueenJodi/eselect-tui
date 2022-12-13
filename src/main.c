#include "eselect.h"
#include "tui.h"
#include "util.h"
#include <stdlib.h>

int main(void) {
	eselect_toggle("vi", 2);
}


int main2(void) {
  setup_tui();

  List *main_list = NULL; // cached for speed

  bool quit = false;

  main_list = get_eselect_modules();
  OptionListVec *option_lists = new_option_list_vec(main_list->length);

  while (!quit) {

    int selection = make_list_tui(main_list);
    if (selection < 0) {
      quit = true;
      exit(0);
    }

    char *name = main_list->items[selection].name;

    if (!option_lists->buff[selection]) {
      OptionList *option_list = get_eselect_options(name);
      option_lists->buff[selection] = option_list;
    }

    make_list_with_selection(option_lists->buff[selection], name);
  }

  free_list(main_list);

  free_optionlistvec(option_lists);

  cleanup_tui();
  return 0;
}

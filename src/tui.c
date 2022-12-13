#include "tui.h"
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include "eselect.h"

int make_list_tui(List *list) {
  clear();

  bool quit = false;

  size_t cursor_index = 0;

  while (!quit) {
    for (size_t i = 0; i < list->length; i++) {
      if (i == cursor_index) {
        attron(A_STANDOUT);
      }
      move(i, 0);

      addstr(list->items[i].name);

      attroff(A_STANDOUT);
    }

    char c = getch();
    switch (c) {
    case 'j': {
      if (cursor_index < list->length - 1) {
        cursor_index += 1;
      }
      break;
    }
    case 'k': {
      if (cursor_index > 0) {
        cursor_index -= 1;
      }
      break;
    }
    case 'l': {
      quit = true;
      break;
    }
    case 'q': {
      cursor_index = -1; // shows the user quit
      quit = true;
      break;
    }
    }

    refresh();
  }
  return cursor_index;
}

void setup_tui(void) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();

  curs_set(0); // make cursor invisible
}

void cleanup_tui(void) {
	curs_set(1);
	endwin();
}

List *new_list(void) {
  List *l = malloc(sizeof(List));
  l->length = 0;
  l->capacity = 5;
  l->items = calloc(l->capacity, sizeof(ListItem));
  return l;
}

void append_list(List *l, char *s) {
  if (l->length == l->capacity) {
    l->capacity *= 2;
    l->items = realloc(l->items, l->capacity * sizeof(ListItem));
  }

  l->items[l->length].name = s;
  l->length += 1;
}

OptionList *new_option_list(void) {
  OptionList *ol = malloc(sizeof(OptionList));

  ol->length = 0;
  ol->capacity = 5;
  ol->options = calloc(ol->capacity, sizeof(Option));

  return ol;
}

void append_option_list(OptionList *ol, char *name, bool enabled) {
  if (ol->length == ol->capacity) {
    ol->capacity *= 2;
    ol->options = realloc(ol->options, sizeof(Option) * ol->capacity);
  }

  ol->options[ol->length] = (Option){name, enabled};
  ol->length += 1;
}

void make_list_with_selection(OptionList *ol, char *name) {
  clear();

  bool quit = false;

  size_t cursor_index = 0;

  printw("%s: ", name);

  while (!quit) {
    for (size_t i = 0; i < ol->length; i++) {
      if (i == cursor_index) {
        attron(A_STANDOUT);
      }
      move(i + 1, 2); // indent slightly

      addstr(ol->options[i].name);

      attroff(A_STANDOUT);
    }

    char c = getch();
    switch (c) {
    case 'j': {
      if (cursor_index < ol->length - 1) {
        cursor_index += 1;
      }
      break;
    }
    case 'k': {
      if (cursor_index > 0) {
        cursor_index -= 1;
      }
      break;
    }
    case 'l': {
      ol->options[cursor_index].is_enabled = true;
			eselect_toggle(name, cursor_index + 1); // add 1 since 0 indexed
      break;
    }
    case 'q': {
      quit = true;
      break;
    }
    case 'h': {
      quit = true;
    }
    }

    refresh();
  }
}

void free_list(List *l) {
  for (size_t i = 0; i < l->length; i++) {
    // free(l->items[i].name);
  }
  free(l->items);
  free(l);
}

void free_option_list(OptionList *ol) {
  for (size_t i = 0; i < ol->length; i++) {
    // free(ol->options->name);
  }
  free(ol->options);
  free(ol);
}

OptionListVec *new_option_list_vec(size_t capacity) {
  OptionListVec *olv = malloc(sizeof(OptionListVec));

  olv->length = 0;
  olv->capacity = capacity;
  olv->buff = calloc(olv->capacity, sizeof(OptionList *));

  return olv;
}
void free_optionlistvec(OptionListVec *olv) {
  for (size_t i = 0; i < olv->length; i++) {
    free(olv->buff[i]);
  }
  free(olv->buff);
  free(olv);
}

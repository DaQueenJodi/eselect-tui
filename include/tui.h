#pragma once
#include "tui.h"
#include <curses.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
typedef struct {
  char *name;
} ListItem;

typedef struct {
  char *name;
  bool is_enabled;
} Option;

typedef struct {
  ListItem *items; // array of list items
  size_t length;
  size_t capacity;
} List;

typedef struct {
  Option *options;
  size_t length;
  size_t capacity;
} OptionList;

void setup_tui(void);

/* returns the index the player chooses */
void cleanup_tui(void);

int make_list_tui(List *list);
void make_list_with_selection(OptionList *list, char *name);

List *new_list(void);
void append_list(List *l, char *name);

OptionList *new_option_list(void);
void append_option_list(OptionList *ol, char *name, bool enabled);

void free_list(List *l);
void free_option_list(OptionList *ol);

typedef struct {
  OptionList **buff;
	size_t capacity;
	size_t length;
} OptionListVec;


OptionListVec *new_option_list_vec(size_t capacity);

void push_optionlistvec(OptionListVec *olv, OptionList *ol);

void free_optionlistvec(OptionListVec *olv);

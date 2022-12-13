#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

typedef struct {
  char *buff;
  size_t capacity;
  size_t length;
} String;

typedef struct {
  String **buff;
  size_t capacity;
  size_t length;
} StringVec;

String *new_string(void);
void string_push(String *s, char c);
void string_push_str(String *s, char *cstr, size_t count);
String *run_shell_command(char *command);

StringVec *new_stringvec(void);
void stringvec_push(StringVec *sv, String *s);


void free_string(String *s);



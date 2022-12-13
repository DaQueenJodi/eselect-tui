#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String *new_string(void) {
  String *s = (String *)malloc(sizeof(String));

  s->capacity = 5;
  s->length = 0;
  s->buff = calloc(sizeof(s->capacity), s->capacity);

  return s;
}

void string_push(String *s, char c) {
  if (s->length == s->capacity) { // if at capacity..
    s->capacity *= 2;             // increase capacity
    s->buff = realloc(s->buff,
                      sizeof(char) * s->capacity); // reallocate entire string
  }

  // place char at end of string and increase lenght
  s->buff[s->length] = c;
  s->length += 1;
}

typedef struct {
  int *buff;
  size_t capacity;
  size_t length;
} IntVec;

IntVec *new_intvec(void);
void intvec_push(IntVec *iv, int i);

String *run_shell_command(char *command) {
  FILE *fp = popen(command, "r");

  if (fp == NULL) {
    eprintf("Failed to run command: %s", command);
    return NULL;
  }
	#define BUFF_SIZE 1
  char buff[BUFF_SIZE];
  String *s = new_string();
	size_t num_bytes;
  while ((num_bytes = fread(buff, sizeof(char),BUFF_SIZE , fp)) != 0) { // use fread since fgets stops at newlines
    string_push_str(s, buff, num_bytes);
  }
  if (pclose(fp) < 0) {
    perror("failed to close command stream: ");
  }
  return s;
}

StringVec *new_stringvec(void) {
  StringVec *sv = malloc(sizeof(StringVec));
  sv->length = 0;
  sv->capacity = 5;
  sv->buff = calloc( sv->capacity, sizeof(String *));
  return sv;
}

void stringvec_push(StringVec *sv, String *s) {
  if (sv->length == sv->capacity) {
    sv->capacity *= 2;
    sv->buff = (String **)realloc(sv->buff, sizeof(String *) * sv->capacity);
  }

  sv->buff[sv->length] = s;
  sv->length += 1;
}

IntVec *new_intvec(void) {
  IntVec *iv = malloc(sizeof(IntVec));

  iv->length = 0;
  iv->capacity = 5;
  iv->buff = (int *)calloc(sizeof(int), iv->capacity);

  return iv;
}

void intvec_push(IntVec *iv, int i) {
  if (iv->length == iv->capacity) {
    iv->capacity *= 2;
    iv->buff = (int *)realloc(iv->buff, sizeof(int) * iv->capacity);
  }

  iv->buff[iv->length] = i;
  iv->length += 1;
}

void string_push_str(String *s, char *cstr, size_t count) {
  if ((s->length + count) > s->capacity) {
    s->capacity = s->length + count;
    s->buff = (char *)realloc(s->buff, s->capacity * sizeof(char));
  }

  memcpy(s->buff + s->length, cstr, sizeof(char) * count);
  s->length += count; 
}



void free_string(String *s) {
	free(s->buff);
	free(s);
}






#include "store.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13

struct entry {
  char *key;
  char *value;
  struct entry *next;
};

typedef struct entry entry;

static entry *hash_table[TABLE_SIZE];

static unsigned long hash_function(const char *string) {
  unsigned long hash = 5381;
  int c = *string;
  while (c != 0) {
    hash = (hash + (hash << 5)) + c;
    string++;
    c = *string;
  }
  return hash % TABLE_SIZE;
}

void store_init() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

void store_print() {
  printf("Start\n");
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("\t%zu\t----\n", i);
    } else {
      entry *p = hash_table[i];
      while (p != NULL) {
        printf("\t%zu\t%s\n", i, p->value);
        p = p->next;
      }
    }
  }
  printf("End\n");
}

bool store_set(const char *key, const char *value) {
  if (key == NULL || value == NULL) {
    return false;
  }
  size_t index = hash_function(key);
  // replacing the value if next call sends the same key
  for (entry *p = hash_table[index]; p != NULL; p = p->next) {
    if (strcmp(p->key, key) == 0) {
      char *new_value = strdup(value);
      if (new_value == NULL) {
        return false;
      }
      free(p->value);
      p->value = new_value;
      return true;
    }
  }
  entry *e = malloc(sizeof(entry));
  if (e == NULL) {
    return false;
  };
  e->key = strdup(key);
  e->value = strdup(value);
  if (e->key == NULL || e->value == NULL) {
    free(e->key);
    free(e->value);
    free(e);
    return false;
  }

  e->next = hash_table[index];
  hash_table[index] = e;
  return true;
}

const char *store_get(const char *key) {
  if (key == NULL) {
    return NULL;
  }
  size_t index = hash_function(key);
  entry *p = hash_table[index];
  if (p == NULL) {
    return NULL;
  }
  while (p != NULL) {
    if (strcmp(key, p->key) == 0) {
      return p->value;
    }
    p = p->next;
  }
  return NULL;
}

void store_free(void) {
  for (size_t i = 0; i < TABLE_SIZE; i++) {
    entry *p = hash_table[i];
    while (p != NULL) {
      entry *next = p->next;
      free(p->key);
      free(p->value);
      free(p);
      p = next;
    }
    hash_table[i] = NULL;
  }
}

bool store_del(const char *key) {
  if (key == NULL) {
    return false;
  }
  size_t index = hash_function(key);

  entry *prev = NULL;
  entry *curr = hash_table[index];

  while (curr != NULL) {
    if (strcmp(curr->key, key) == 0) {
      if (prev == NULL) {
        hash_table[index] = curr->next;
      } else {
        prev->next = curr->next;
      }
      free(curr->key);
      free(curr->value);
      free(curr);
      return true;
    }
    prev = curr;
    curr = curr->next;
  }
  return false;
}

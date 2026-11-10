

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define TABLE_SIZE 13

struct entry {
  char *key;
  char *value;
  struct entry *next;
};

typedef struct entry entry;

entry *hash_table[TABLE_SIZE];

unsigned long hash_function(const char *string) {
  unsigned long hash = 5381;
  int c = *string;
  while (c != 0) {
    hash = (hash + (hash << 5)) + c;
    string++;
    c = *string;
  }
  return hash % TABLE_SIZE;
}

void init_hash_table() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hash_table[i] = NULL;
  }
}

void print_table() {
  printf("Start\n");
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i] == NULL) {
      printf("\t%d\t----\n", i);
    } else {
      entry *p = hash_table[i];
      while (p != NULL) {
        printf("\t%d\t%s\n", i, p->value);
        p = p->next;
      }
    }
  }
  printf("End\n");
}

bool set(char *key, char *value) {
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

char *get(const char *key) {
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

int main() {
  init_hash_table();
  set("name", "Ali");
  set("name", "Aadi");
  print_table();
  printf("%s\n", get("name"));
  return 0;
}

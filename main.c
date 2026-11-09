

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#define TABLE_SIZE 13
char *hash_table[TABLE_SIZE];

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
      printf("\t%d\t%s\n", i, hash_table[i]);
    }
  }
  printf("End\n");
}

bool add_to_table(char *name) {
  if (name == NULL) {
    return false;
  }
  int index = hash_function(name);
  if (hash_table[index] != NULL) {
    return false;
  }
  hash_table[index] = name;
  return true;
}

int main() {
  char *s = "ball";
  init_hash_table();
  print_table();
  add_to_table(s);
  print_table();
  return 0;
}

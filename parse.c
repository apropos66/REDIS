#include "store.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

int split_line(char *line, char **words, int max_words) {
  int count = 0;
  int i = 0;

  while (line[i] != '\0') {
    while (line[i] != '\0' && is_space(line[i])) {
      i++;
    }

    if (line[i] == '\0')
      break;

    if (count >= max_words)
      return -1;

    words[count] = &line[i];
    count++;

    while (line[i] != '\0' && !is_space(line[i])) {
      i++;
    }

    if (line[i] != '\0') {
      line[i] = '\0';
      i++;
    }
  }
  return count;
}

void execute(int count, char **words, char *reply, size_t reply_size) {
  if (count == 0) {
    strcpy(reply, "Invalid command!\r\n");
    return;
  }

  if (count == -1) {
    strcpy(reply, "Command too long!\r\n");
    return;
  }

  if (count == 3 && strcmp(words[0], "SET") == 0) {
    store_set(words[1], words[2]);
    strcpy(reply, "Storage successful!\r\n");
    return;
  }

  if (count == 2 && strcmp(words[0], "GET") == 0) {
    const char *value = store_get(words[1]);
    strcpy(reply, value);
    return;
  }

  if (count == 2 && strcmp(words[0], "DEL") == 0) {
    store_del(words[1]);
    strcpy(reply, "Deletion successful!\r\n");
    return;
  }
  strcpy(reply, "Invalid Command\r\n");
}

int main() {
  char line[] = "hello its me aaditya";
  int max_words = 10;
  char *words[max_words];
  int result = split_line(line, words, max_words);
  printf("%d\n", result);
  printf("%s\n", words[0]);
  printf("%s\n", words[1]);
  printf("%s\n", words[2]);
  printf("%s\n", words[3]);
  printf("%s\n", words[4]);
}

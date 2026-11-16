#include "parse.h"
#include "store.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

void parse_line(char *line, char *reply, int reply_size);

static int is_space(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int parse_split_line(char *line, char **words, int max_words) {
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

static void parse_execute(int count, char **words, char *reply,
                          size_t reply_size) {
  if (count == 0) {
    strcpy(reply, "Invalid command!\r\n");
    return;
  }

  if (count == -1) {
    strcpy(reply, "Command too long!\r\n");
    return;
  }

  if (strcasecmp(words[0], "SET") == 0) {
    if (count != 3) {
      strcpy(reply, "Wrong argument count!\r\n");
      return;
    }
    bool status = store_set(words[1], words[2]);
    if (status == true) {
      strcpy(reply, "Storage successful!\r\n");
      return;
    }
    if (status == false) {
      strcpy(reply, "Storage failed!\r\n");
      return;
    }
  }

  if (strcasecmp(words[0], "GET") == 0) {
    if (count != 2) {
      strcpy(reply, "Wrong argument count!\r\n");
      return;
    }
    const char *value = store_get(words[1]);
    if (value != NULL) {
      if (strlen(value) >= reply_size) {
        strcpy(reply, "Reply length too long!\r\n");
        return;
      }
      strcpy(reply, value);
      strcat(reply, "\r\n");
      return;
    }

    if (value == NULL) {
      strcpy(reply, "Invalid key!\r\n");
      return;
    }
  }

  if (strcasecmp(words[0], "DEL") == 0) {
    if (count != 2) {
      strcpy(reply, "Wrong argument count!\r\n");
      return;
    }
    bool status = store_del(words[1]);
    if (status == true) {
      strcpy(reply, "Deletion successful!\r\n");
      return;
    }
    if (status == false) {
      strcpy(reply, "Invalid key!\r\n");
      return;
    }
  }
  strcpy(reply, "Invalid Command\r\n");
}

void parse_line(char *line, char *reply, int reply_size) {
  int max_words = 10;
  char *words[max_words];
  int count = parse_split_line(line, words, max_words);
  parse_execute(count, words, reply, reply_size);
}

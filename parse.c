#include <stdio.h>

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

int main() {
  char line[] = "hello its me aaditya";
  int max_words = 10;
  char *words[max_words];
  int result = split_line(line, words, max_words);
  printf("%d", result);
}

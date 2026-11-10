#ifndef STORE_H
#define STORE_H

#include <stdbool.h>

void store_init(void);
bool store_set(const char *key, const char *value);
const char *store_get(const char *key);
bool store_del(const char *key);
void store_print(void);
void store_free(void);

#endif

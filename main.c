#include "store.h"

#include <stdio.h>

int main(void) {
  store_print();
  store_set("user:1:name", "Ali");
  store_set("user:2:name", "Jiya");
  store_print();
}

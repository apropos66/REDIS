

#include "store.h"

int main(void) {
  store_print();
  store_set("user:1:name", "Ali");
  store_set("user:2:name", "Baba");
  store_print();
  return 0;
}

#include "./utils.h"
#include <stdlib.h>

void safe_free(void *ptr) {
  free(ptr);
  ptr = NULL;
}

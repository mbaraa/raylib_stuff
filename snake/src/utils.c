#include "./utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void safe_free(void *ptr) {
  free(ptr);
  ptr = NULL;
}

char *itoa(int n) {
  if (n <= 0) {
    n++;
  }
  size_t str_len = (int)((ceil(log10(n)) + 1) * sizeof(char));
  char *str = (char *)malloc(str_len);
  sprintf(str, "%d", n);

  return str;
}

bool compare_colors(Color c1, Color c2) {
  return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

#ifndef _UTILS_H
#define _UTILS_H

#include <raylib.h>
#include <stdbool.h>

void safe_free(void *ptr);
char *itoa(int n);
bool compare_colors(Color c1, Color c2);

#endif // !_UTILS_H

#ifndef STRUTILS_H
#define STRUTILS_H

#include <stdlib.h>
#include <string.h>

char *replace(const char *s, char ch, const char *repl);
char *push_str(char *s, char *ch);

#endif

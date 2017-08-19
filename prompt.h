#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char *func_names[];

char *strdup (const char *s);
char *strndup (const char *s, size_t n);
char *type_prompt (char *command);
char *type_file (char *file);

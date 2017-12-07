#ifndef _PROMPT_H
#define _PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void prompt_init (char **names);
char *strdup (const char *s);
char *strndup (const char *s, size_t n);
char *type_prompt (char *command);
char *type_file (char *file);

#endif

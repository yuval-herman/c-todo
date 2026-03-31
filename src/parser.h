#include <stdbool.h>

#include "types.h"

unsigned int skip_blank(const char *str);
unsigned int skip_num(const char *str);
unsigned int skip_alpha(const char *str);
unsigned int skip_to_blank(const char *str);

char *DateToStr(TodoDate date);
bool isDateEmpty(TodoDate date);

TodoItem parser_parseTodoString(const char *str);

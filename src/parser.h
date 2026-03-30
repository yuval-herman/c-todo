#include <stdbool.h>

#include "types.h"

void addTag(TodoItem *todo, char *tag);
void addContext(TodoItem *todo, char *context);
unsigned int skip_blank(const char *str);
unsigned int skip_num(const char *str);
unsigned int skip_alpha(const char *str);
unsigned int skip_to_blank(const char *str);
char *DateToStr(Date date);
bool isDateEmpty(Date date);
TodoItem parseTodoString(const char *str);

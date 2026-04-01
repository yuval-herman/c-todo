#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "manager.h"
#include "parser.h"
#include "types.h"

unsigned int skip_blank(const char *str) {
  unsigned int pos = 0;
  while (str[pos] != '\0' && isblank(str[pos])) {
    pos++;
  }
  return pos;
}

unsigned int skip_num(const char *str) {
  unsigned int pos = 0;
  while (str[pos] != '\0' && isdigit(str[pos])) {
    pos++;
  }
  return pos;
}

unsigned int skip_alpha(const char *str) {
  unsigned int pos = 0;
  while (str[pos] != '\0' && isalpha(str[pos])) {
    pos++;
  }
  return pos;
}

unsigned int skip_to_blank(const char *str) {
  unsigned int pos = 0;
  while (str[pos] != '\0' && !isblank(str[pos])) {
    pos++;
  }
  return pos;
}

char datePrintBuf[11];
char *DateToStr(TodoDate date) {
  snprintf(datePrintBuf, 11, "%u/%u/%u", date.year, date.month, date.day);
  return datePrintBuf;
}

bool isDateEmpty(TodoDate date) {
  return date.year == 0 && date.month == 0 && date.day == 0;
}

bool parser_parseTodoString(TodoItem *todo, const char *str) {
  *todo = (TodoItem){0};
  unsigned int pos = 0;

  // Example todo:
  // (A) 2026-03-26 A test item! +Todo-mangaer-project @Programming

  // Priority is optional, but always appears first if it exists
  if (str[0] == '(' && str[2] == ')') {
    if (!isalpha(str[1])) {
      printf("Warning: illegal priority (%c), registering as (%c)", str[1],
             DEFAULT_PRIORITY);
      todo->priority = DEFAULT_PRIORITY;
    } else {
      todo->priority = (char)toupper(str[1]);
    }
    pos += 3;
  } else {
    todo->priority = 0;
  }

  pos += skip_blank(str + pos);

  // Creation date is optional, but always appears right after the priority,
  // or at the start if the former does not exist
  int year, month, day;
  int res = sscanf(str + pos, "%4d-%2d-%2d", &year, &month, &day);
  if (res == 3 && year > 0 && month > 0 && day > 0) {
    todo->creation_date.year = (unsigned)year;
    todo->creation_date.month = (unsigned)month;
    todo->creation_date.day = (unsigned)day;
    pos += 10;
  }

  todo->description = strdup(str + pos + skip_blank(str + pos));

  // Tags and context can appears anywhere in the string
  while (str[pos] != '\0') {
    // This is a tag
    if (str[pos] == '+') {
      unsigned int tag_end = pos + skip_to_blank(str + pos);
      manager_addTag(todo, strndup(str + pos, tag_end - pos));
      pos = tag_end - 1;
    }
    // This is a context
    else if (str[pos] == '@') {
      unsigned int context_end = pos + skip_to_blank(str + pos);
      manager_addContext(todo, strndup(str + pos, context_end - pos));
      pos = context_end - 1;
    }
    ++pos;
  }

  return todo;
}

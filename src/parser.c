#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

// Tag is used directly, if you intend to change the string later, call strdup
// on it first
void parser_addTag(TodoItem *todo, char *tag) {
  unsigned int new_tags_amount = todo->tags_amount + 1;
  todo->tags = realloc(todo->tags, sizeof(todo->tags[0]) * new_tags_amount);
  todo->tags[todo->tags_amount] = tag;
  todo->tags_amount = new_tags_amount;
}

// Context is used directly, if you intend to change the string later, call
// strdup on it first
void parser_addContext(TodoItem *todo, char *context) {
  unsigned int new_context_amount = todo->context_amount + 1;
  todo->context =
      realloc(todo->context, sizeof(todo->context[0]) * new_context_amount);
  todo->context[todo->context_amount] = context;
  todo->context_amount = new_context_amount;
}

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

TodoItem parser_parseTodoString(const char *str) {
  TodoItem todo = {0};
  unsigned int pos = 0;

  // Example todo:
  // (A) 2026-03-26 A test item! +Todo-mangaer-project @Programming

  // Priority is optional, but always appears first if it exists
  if (str[0] == '(' && str[2] == ')') {
    if (!isalpha(str[1])) {
      printf("Warning: illegal priority (%c), registering as (%c)", str[1],
             DEFAULT_PRIORITY);
      todo.priority = DEFAULT_PRIORITY;
    } else {
      todo.priority = (char)toupper(str[1]);
    }
    pos += 3;
  } else {
    todo.priority = 0;
  }

  pos += skip_blank(str + pos);

  // Creation date is optional, but always appears right after the priority,
  // or at the start if the former does not exist
  unsigned int year, month, day;
  int res = sscanf(str + pos, "%u-%u-%u", &year, &month, &day);
  if (res == 3) {
    todo.creation_date.year = year;
    todo.creation_date.month = month;
    todo.creation_date.day = day;
    pos += 10;
  }

  todo.description = strdup(str + pos + skip_blank(str + pos));

  // Tags and context can appears anywhere in the string
  while (str[pos] != '\0') {
    // This is a tag
    if (str[pos] == '+') {
      unsigned int tag_end = pos + skip_to_blank(str + pos);
      parser_addTag(&todo, strndup(str + pos, tag_end - pos));
      pos = tag_end;
    }
    // This is a context
    else if (str[pos] == '@') {
      unsigned int context_end = pos + skip_to_blank(str + pos);
      parser_addContext(&todo, strndup(str + pos, context_end - pos));
      pos = context_end;
    }
    ++pos;
  }

  return todo;
}

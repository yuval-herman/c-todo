#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PRIORITY 'C'

char *todo_file = "./todo.txt";

typedef struct {
  unsigned int year, month, day;
} Date;

typedef struct {
  char *description;
  char **context;
  char **tags;
  unsigned int context_amount;
  unsigned int tags_amount;
  Date creation_date; // 0 value is no time set
  // This was not in the original spec, for now we won't support this
  // Date due_date;      // 0 value is no time set
  char priority; // A single letter 'A' is highest priority, 'Z' is lowest, 0
                 // value is no priority set
} TodoItem;

// Tag is used directly, if you intend to char the string later, call strdup on
// it first
void addTag(TodoItem *todo, char *tag) {
  unsigned int new_tags_amount = todo->tags_amount + 1;
  todo->tags = realloc(todo->tags, sizeof(todo->tags[0]) * new_tags_amount);
  todo->tags[todo->tags_amount] = tag;
  todo->tags_amount = new_tags_amount;
}

// Context is used directly, if you intend to char the string later, call strdup
// on it first
void addContext(TodoItem *todo, char *context) {
  unsigned int new_context_amount = todo->context_amount + 1;
  todo->context =
      realloc(todo->context, sizeof(todo->context[0]) * new_context_amount);
  todo->context[todo->context_amount] = context;
  todo->context_amount = new_context_amount;
}

unsigned int skip_blank(const char *str) {
  unsigned int pos = 0;
  while (isblank(str[pos])) {
    pos++;
  };
  return pos;
}

unsigned int skip_num(const char *str) {
  unsigned int pos = 0;
  while (isdigit(str[pos])) {
    pos++;
  };
  return pos;
}

unsigned int skip_alpha(const char *str) {
  unsigned int pos = 0;
  while (isalpha(str[pos])) {
    pos++;
  };
  return pos;
}

unsigned int skip_to_blank(const char *str) {
  unsigned int pos = 0;
  while (!isblank(str[pos])) {
    pos++;
  };
  return pos;
}

char datePrintBuf[11];
char *DateToStr(Date date) {
  snprintf(datePrintBuf, 11, "%u/%u/%u", date.year, date.month, date.day);
  return datePrintBuf;
}

bool isDateEmpty(Date date) {
  return date.year == 0 && date.month == 0 && date.day == 0;
}

TodoItem parseTodoString(const char *str) {
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
      todo.priority = toupper(str[1]);
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
      addTag(&todo, strndup(str + pos, tag_end - pos));
      pos = tag_end;
    }
    // This is a context
    else if (str[pos] == '@') {
      unsigned int context_end = pos + skip_to_blank(str + pos);
      addContext(&todo, strndup(str + pos, context_end - pos));
      pos = context_end;
    }
    ++pos;
  }

  return todo;
}

void printTodoItem(TodoItem item) {
  printf("description = %s\n", item.description);

  if (item.priority)
    printf("priority    = %c\n", item.priority);
  else
    printf("priority    = (not set)\n");

  if (!isDateEmpty(item.creation_date))
    printf("start_date  = %s\n", DateToStr(item.creation_date));
  // if (!isDateEmpty(item.due_date))
  //   printf("due_date    = %s\n", DateToStr(item.due_date));

  if (item.context_amount) {
    printf("\nContext:\n");
    for (unsigned int i = 0; i < item.context_amount; ++i) {
      printf("\t%s\n", item.context[i]);
    }
  }
  if (item.tags_amount) {
    printf("\nTags:\n");
    for (unsigned int i = 0; i < item.tags_amount; ++i) {
      printf("\t%s\n", item.tags[i]);
    }
  }
}

// !!This does not free a todo pointer!!
// Call this to free context and tags and other strings. to free a todo struct,
// just call free on it
void freeTodo(TodoItem todo) {
  free(todo.description);
  for (unsigned int i = 0; i < todo.context_amount; ++i) {
    free(todo.context[i]);
  }
  free(todo.context);
  for (unsigned int i = 0; i < todo.tags_amount; ++i) {
    free(todo.tags[i]);
  }
  free(todo.tags);
}

int main(int argc, char **argv) {
  TodoItem todo = parseTodoString(argv[1]);
  printTodoItem(todo);
  freeTodo(todo);
  return 0;
}

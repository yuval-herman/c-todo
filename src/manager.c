#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "manager.h"
#include "parser.h"
#include "../nob.h"

// Used for printing todos
String_Builder todo_repr = {0};

// String is only valid until next call to any manager function
static char* manager_todoToString(TodoItem item) {
  todo_repr.count = 0;

  sb_appendf(&todo_repr,"description = %s\n", item.description);

  if (item.priority)
    sb_appendf(&todo_repr,"priority    = %c\n", item.priority);
  else
    sb_appendf(&todo_repr,"priority    = (not set)\n");

  if (!isDateEmpty(item.creation_date))
    sb_appendf(&todo_repr,"start_date  = %s\n", DateToStr(item.creation_date));
  // if (!isDateEmpty(item.due_date))
  //   sb_appendf(&todo_repr,"due_date    = %s\n", DateToStr(item.due_date));

  if (item.context_amount) {
    sb_appendf(&todo_repr,"\nContext:\n");
    for (unsigned int i = 0; i < item.context_amount; ++i) {
      sb_appendf(&todo_repr,"\t%s\n", item.context[i]);
    }
  }
  if (item.tags_amount) {
    sb_appendf(&todo_repr,"\nTags:\n");
    for (unsigned int i = 0; i < item.tags_amount; ++i) {
      sb_appendf(&todo_repr,"\t%s\n", item.tags[i]);
    }
  }

  return todo_repr.items;
}

void manager_printTodoItem(TodoItem item) {
  puts(manager_todoToString(item));
}

TodoItem manager_todoFromString(char* str) {
 return parser_parseTodoString(str); 
}

// Tag is used directly, if you intend to change the string later, call strdup
// on it first
void manager_addTag(TodoItem *todo, char *tag) {
  unsigned int new_tags_amount = todo->tags_amount + 1;
  todo->tags = realloc(todo->tags, sizeof(todo->tags[0]) * new_tags_amount);
  todo->tags[todo->tags_amount] = tag;
  todo->tags_amount = new_tags_amount;
}

// Context is used directly, if you intend to change the string later, call
// strdup on it first
void manager_addContext(TodoItem *todo, char *context) {
  unsigned int new_context_amount = todo->context_amount + 1;
  todo->context =
      realloc(todo->context, sizeof(todo->context[0]) * new_context_amount);
  todo->context[todo->context_amount] = context;
  todo->context_amount = new_context_amount;
}

TodoDA manager_readTodoFile(const char* filename) {
  char* line = NULL;
  size_t len=0;

  FILE* todo_file = fopen(filename, "r");
  if(todo_file == NULL) {
    perror("Failed opening");
    // Need to make a universal error reporter
    exit(1);
  }
}
TodoDA manager_writeTodosToFile(TodoDA todos, const char *filename);

// !!This does not free a todo pointer!!
// Call this to free context and tags and other strings. to free a todo struct,
// just call free on it
void manager_freeTodo(TodoItem todo) {
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

void manager_destroy() {
  sb_free(todo_repr);
}

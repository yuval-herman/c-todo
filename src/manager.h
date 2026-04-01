#ifndef MANAGER_H
#define MANAGER_H

#include "types.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
  TodoItem *items;
  size_t count;
  size_t capacity;
} TodoDA;

void manager_printTodoItem(TodoItem item);
bool manager_todoFromString(TodoItem *item, char *str);

// Tag is used directly, if you intend to change the string later, call strdup
// on it first
void manager_addTag(TodoItem *todo, char *tag);
// Context is used directly, if you intend to change the string later, call
// strdup on it first
void manager_addContext(TodoItem *todo, char *context);

bool manager_readTodoFile(TodoDA *item, const char *filename);
bool manager_writeTodosToFile(TodoDA *todos, const char *filename);

void manager_freeTodo(TodoItem todo);

// Destroys all resources allocated by manager
void manager_destroy();

#endif // MANAGER_H

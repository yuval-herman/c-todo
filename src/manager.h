#ifndef MANAGER_H
#define MANAGER_H

#include "types.h"
#include <stddef.h>

typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} TodoDA;

void manager_printTodoItem(TodoItem item);
TodoItem manager_todoFromString(char* str);

// Tag is used directly, if you intend to change the string later, call strdup
// on it first
void manager_addTag(TodoItem *todo, char *tag);
// Context is used directly, if you intend to change the string later, call
// strdup on it first
void manager_addContext(TodoItem *todo, char *context);

TodoDA manager_readTodoFile(const char* filename);
TodoDA manager_writeTodosToFile(TodoDA todos, const char *filename);

void manager_freeTodo(TodoItem todo);

// Destroys all resources allocated by manager
void manager_destroy();

#endif // MANAGER_H

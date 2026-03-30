#include <stdio.h>
#include <stdlib.h>

#include "manager.h"
#include "parser.h"

void manager_printTodoItem(TodoItem item) {
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

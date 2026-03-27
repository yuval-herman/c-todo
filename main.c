#include <stdio.h>
#include <time.h>

char *todo_file = "./todo.txt";

typedef struct {
  char *description;
  char *context;
  char *project;
  char **tags;
  unsigned int tags_amount;
  unsigned int priority;
  time_t start_date; // 0 value is no time set
  time_t due_date;   // 0 value is no time set
} TodoItem;

// TodoItem parseTodoString(const char *str) {}

void printTodoItem(TodoItem item) {
  printf("description = %s\n"
         "context     = %s\n"
         "project     = %s\n"
         "priority    = %u\n",
         item.description, item.context, item.project, item.priority);

  if (item.start_date)
    printf("start_date  = %s", ctime(&item.start_date));
  if (item.due_date)
    printf("due_date    = %s", ctime(&item.due_date));

  if (item.tags_amount) {
    printf("\nTags:\n");
    for (unsigned int i = 0; i < item.tags_amount; ++i) {
      printf("\t%s\n", item.tags[i]);
    }
  }
}

int main(int argc, char **argv) {
  // for (int i = 0; i < argc; ++i) {
  //   printf("args[%d] = %s\n", i, argv[i]);
  // }
  //
  printTodoItem((TodoItem){
      .description = "A test item!",
      .context = "Programming",
      .project = "Todo mangaer project",
      .tags = (char *[]){"Computer", "c-programming", "fun-project"},
      .tags_amount = 3,
      .priority = 100,
      .start_date = time(NULL),
      .due_date = 0,
  });

  return 0;
}

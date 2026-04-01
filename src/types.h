#ifndef TYPES_H
#define TYPES_H

#define reportError(err_fmt, ...)                                              \
  fprintf(stderr, "%.*s: " err_fmt,                                            \
          (int)(strrchr(__FILE_NAME__, '.') - __FILE_NAME__), __FILE_NAME__,   \
          ##__VA_ARGS__)

#define returnIfError(expr)                                                    \
  do {                                                                         \
    if (!expr)                                                                  \
      return false;                                                            \
  } while (0)

#define DEFAULT_PRIORITY 'C'

typedef struct {
  unsigned int year, month, day;
} TodoDate;

typedef struct {
  char *description;
  char **context;
  char **tags;
  unsigned int context_amount;
  unsigned int tags_amount;
  TodoDate creation_date; // 0 value is no time set
  // This was not in the original spec, for now we won't support this
  // Date due_date;      // 0 value is no time set
  char priority; // A single letter 'A' is highest priority, 'Z' is lowest, 0
                 // value is no priority set
} TodoItem;

#endif // TYPES_H

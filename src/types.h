#ifndef TYPES_H
#define  TYPES_H

#define DEFAULT_PRIORITY 'C'

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

#endif // TYPES_H

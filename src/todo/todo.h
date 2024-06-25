#ifndef TODO
#define TODO

#include <sqlite3.h>

struct Todo {
    int id;
    char* task;
    char* priority;
    int is_completed;
};

void seed_db();
void insert_task(struct Todo todo);
void delete_task(int id);
char* get_task_in_json(int id);
struct Todo *todo_from_json(char* json);
char* get_all_tasks_in_json();
void update_task(int id, struct Todo todo);

#endif // !TODO

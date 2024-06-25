#include "todo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

sqlite3 *DB;

char *DB_FILE = "data.db";

void seed_db() {
  char *err_msg = 0;
  sqlite3_open(DB_FILE, &DB);
  int rc = sqlite3_exec(DB,
                        "CREATE TABLE IF NOT EXISTS todos (id BIGINT PRIMARY "
                        "KEY, name TEXT, priority TEXT, is_completed INT);",
                        0, 0, &err_msg);
  if (rc != SQLITE_OK) {
    sqlite3_free(err_msg);
  }
}


void insert_task(struct Todo todo) {
  char *err_msg = 0;
  sqlite3_open(DB_FILE, &DB);
  char sql[100];
  sprintf(sql, "INSERT INTO todos VALUES (%d, '%s', '%s', '%d');", todo.id,
          todo.task, todo.priority, todo.is_completed);
  int rc = sqlite3_exec(DB, sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
    sqlite3_free(err_msg);
  }
}

char *get_task_in_json(int id) {
  char *err_msg = 0;
  sqlite3_open(DB_FILE, &DB);
  char sql[100];
  sprintf(sql, "SELECT * FROM todos WHERE id=%d;", id);
  sqlite3_stmt *res;
  int rc = sqlite3_prepare_v2(DB, sql, -1, &res, 0);
  struct Todo todo;
    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
      todo.id = sqlite3_column_int(res, 0);
      todo.task = (char*) sqlite3_column_text(res, 1);
      todo.priority = (char *) sqlite3_column_text(res, 2);
      todo.is_completed = sqlite3_column_int(res, 3);
  char *json = (char *)malloc(100 * sizeof(char));
  sprintf(json, "{ message: \"Task found\",data: {\"id\":%d, \"task\":\"%s\", \"priority\":\"%s\", "
                "\"is_completed\":%d}}",
          todo.id, todo.task, todo.priority, todo.is_completed);

  return json;
    } else {
      return "{message: \"Task not found\", data: {}}";
    }
  sqlite3_finalize(res);
}

char* get_all_tasks_in_json() {
  char *err_msg = 0;
  sqlite3_open(DB_FILE, &DB);
  char sql[100];
  sprintf(sql, "SELECT * FROM todos;");
  sqlite3_stmt *res;
  int rc = sqlite3_prepare_v2(DB, sql, -1, &res, 0);
  char *json = (char *)malloc(1000 * sizeof(char));
  sprintf(json, "{ \"message\": \"Tasks found\", \"data\": [");
  int count = sqlite3_column_count(res);
  int i = 1;
  while (sqlite3_step(res) == SQLITE_ROW) {
    int id = sqlite3_column_int(res, 0);
    char *task = (char *)sqlite3_column_text(res, 1);
    char *priority = (char *)sqlite3_column_text(res, 2);
    char is_completed = sqlite3_column_int(res, 3);
    char *task_json = (char *)malloc(100 * sizeof(char));
    // do not put comma after last task 
    if (i == 1) {
      sprintf(task_json, "{\"id\":%d, \"task\":\"%s\", \"priority\":\"%s\", "
                "\"is_completed\":%d}",
                id, task, priority, is_completed);
    } else {
      // no comma at the beginnign of first task 
      sprintf(task_json, ",{\"id\":%d, \"task\":\"%s\", \"priority\":\"%s\", "
                "\"is_completed\":%d}",

                id, task, priority, is_completed);
    }
    i++;
    strcat(json, task_json);
  }
  strcat(json, "]}");
  return json;
  sqlite3_finalize(res);
}

struct Todo *todo_from_json(char *json) {
  if (json == NULL) {
    fprintf(stderr, "Error: input JSON string is NULL\n");
    return NULL;
  }

  struct Todo *todo = malloc(sizeof(struct Todo));
  if (todo == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for Todo struct\n");
    return NULL;
  }

  char *id_start = strstr(json, "\"id\":");
  char *task_start = strstr(json, "\"task\":\"");
  char *priority_start = strstr(json, "\"priority\":\"");
  char *is_completed_start = strstr(json, "\"is_completed\":");

  if (id_start == NULL || task_start == NULL || priority_start == NULL ||
      is_completed_start == NULL) {
    fprintf(stderr, "Error: input JSON string is not well-formed\n");
    free(todo);
    return NULL;
  }

  if (sscanf(id_start + 5, "%d", &todo->id) != 1) {
    fprintf(stderr, "Error: failed to parse id from JSON string\n");
    free(todo);
    return NULL;
  }

  char *task_end = strstr(task_start + 8, "\"");
  if (task_end == NULL) {
    fprintf(stderr, "Error: failed to parse task from JSON string\n");
    free(todo);
    return NULL;
  }
  int task_len = task_end - task_start - 8;
  todo->task = malloc(task_len + 1);
  if (todo->task == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for task string\n");
    free(todo);
    return NULL;
  }
  strncpy(todo->task, task_start + 8, task_len);
  todo->task[task_len] = '\0';

  char *priority_end = strstr(priority_start + 12, "\"");
  if (priority_end == NULL) {
    fprintf(stderr, "Error: failed to parse priority from JSON string\n");
    free(todo->task);
    free(todo);
    return NULL;
  }
  int priority_len = priority_end - priority_start - 12;
  todo->priority = malloc(priority_len + 1);
  if (todo->priority == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for priority string\n");
    free(todo->task);
    free(todo);
    return NULL;
  }
  strncpy(todo->priority, priority_start + 12, priority_len);
  todo->priority[priority_len] = '\0';

  char *is_completed_end = strstr(is_completed_start + 15, ",");
  if (is_completed_end == NULL) {
    is_completed_end = strstr(is_completed_start + 15, "}");
  }
  if (is_completed_end == NULL) {
    fprintf(stderr, "Error: failed to parse is_completed from JSON string\n");
    free(todo->task);
    free(todo->priority);
    free(todo);
    return NULL;
  }
  int is_completed_len = is_completed_end - (is_completed_start + 15);
  char *is_completed_str = malloc(is_completed_len + 1);
  if (is_completed_str == NULL) {
    fprintf(stderr,
            "Error: failed to allocate memory for is_completed string\n");
    free(todo->task);
    free(todo->priority);
    free(todo);
    return NULL;
  }
  strncpy(is_completed_str, is_completed_start + 15, is_completed_len);
  is_completed_str[is_completed_len] = '\0';
  todo->is_completed = atoi(is_completed_str);
  free(is_completed_str);

  return todo;
}
void update_task(int id, struct Todo todo) {
  char *err_msg = 0;
  sqlite3_stmt *stmt;
  sqlite3_open(DB_FILE, &DB);
  char sql[100];
  printf("SHOULD IT BE COMPLETE: %d\n", todo.is_completed);
  sprintf(sql, "UPDATE todos SET name='%s', priority='%s', is_completed=%d "

               "WHERE id=%d;",
          todo.task, todo.priority, todo.is_completed, id);
  int rc = sqlite3_prepare_v2(
      DB, sql, -1, &stmt, NULL);

  rc = sqlite3_step(stmt);

  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(DB));
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(DB);
}

void delete_task(int id) {
  char *err_msg = 0;
  sqlite3_open(DB_FILE, &DB);
  char sql[100];
  sprintf(sql, "DELETE FROM todos WHERE id=%d;", id);
  int rc = sqlite3_exec(DB, sql, 0, 0, &err_msg);
  if (rc != SQLITE_OK) {
    sqlite3_free(err_msg);
  }
}

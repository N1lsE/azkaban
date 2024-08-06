#include "db_manager.h"
#include "entry.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void *callback(void *not_used, Entry entry) {
  printf("id = %d\n", entry.id);
  printf("name = %s\n", entry.name);
  printf("user_name = %s\n", entry.user_name);
  printf("\n");
}

int main(int argc, char *argv[]) {
  printf("Hello from azkaban\n");

  const char *filename = "test.azk";
  const char *password = "123";
  sqlite3 *db = db_open(filename, password);

  Entry e;
  e.id = -1;
  e.name = "test_out_of_program";
  e.user_name = "toop";
  e.password = "toop_pw";
  int rc = db_write_entry(db, e);
  printf("insert status: %d\n", rc);

  EntryNode *entry_list = db_get_all_entries(db);
  // entry_list_itterate_function(entry_list, callback, 0);

  srand(time(NULL));
  int entry_list_length = entry_list_get_length(entry_list);
  int r = 1;
  if (entry_list_length > 1) {
    r = (rand() % (entry_list_length - 1)) + 1;
  }
  printf("rand: %d\n", r);
  if (r >= 0) {
    EntryDetail entry_detail;
    IContent *i_content;
    entry_detail.id = -1;
    entry_detail.f_entry_id = r;
    entry_detail.content = (IContent *)malloc(sizeof(IContent));
    entry_detail.content->type = "text";
    char *t = "Test Detail 123";
    entry_detail.content->data.text = t;
    entry_detail.content->size = strlen(t);
    db_write_entryDetail(db, entry_detail);
  }

  db_close(db);

  printf("entries: %d\n", entry_list_get_length(entry_list));
  return 0;
}

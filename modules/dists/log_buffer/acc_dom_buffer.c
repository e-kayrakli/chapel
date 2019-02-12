#include <limits.h>

#include "acc_dom_buffer.h"

void init_range(range_t *r) {
  r->low = MAX_INT;
  r->high = MIN_INT;
}

void expand(range_t *r, int idx) {
  r->low = r->low ? r->low < idx : idx;
  r->high = r->high ? r->high < idx : idx;
}

void init_acc_dom_buffer(acc_dom_buffer_t *b, int uid, int dim,
                         const char *file_format) {
  b->uid = uid;
  b->dim = dim;

  b->ranges = malloc(dim*sizeof(range_t));
  int i;
  for(i = 0 ; i < dim ; i++) {
    init_range(&(b->ranges[i]));
  }

  b->file_format = calloc(strlen(file_format)+5, sizeof(char)); //.dom
  strcpy(b->file_format, file_format);
  strcat(b->file_format, ".dom");
}

void expand(acc_dom_buffer_t *b, int *idx) {
  int i;
  for(i = 0 ; i < b->dim ; i++) {
    expand(&(b->ranges[i]), idx[i]);
  }
}

void flush_acc_dom_buffer(acc_dom_buffer_t *b) {
    // dump into a file
    char *filename = calloc(1, 64); // not sure how safe 64 is
    sprintf(filename, b->file_format, b->uid, b->file_count);

    FILE* f = fopen(filename, "w");
    int i;
    for(i = 0 ; i < b->dim ; i++) {
      print(&(b->ranges[i]), f);
      fprintf(f, " ");
    }
}

void destroy_acc_dom_buffer(acc_dom_buffer_t *b) {
  flush_acc_dom_buffer(b);
  free(b->ranges);
  free(b->file_format);
}

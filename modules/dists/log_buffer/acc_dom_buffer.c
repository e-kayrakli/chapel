#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "acc_dom_buffer.h"

void init_range(range_t *r) {
  r->low = INT_MAX;
  r->high = INT_MIN;
}

void expand_range(range_t *r, int idx) {
  r->low = r->low < idx ? r->low : idx;
  r->high = r->high > idx ? r->high : idx;
}

void print(range_t *r, FILE *f) {
  fprintf(f, "%d %d", r->low, r->high);
}

void init_subbuf(acc_dom_buffer_t *b, int uid, size_t cap, int dim,
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

void append_to_subbuf(acc_dom_buffer_t *b, int *idx) {
  int i;
  for(i = 0 ; i < b->dim ; i++) {
    expand_range(&(b->ranges[i]), idx[i]);
  }
}

void dump_subbuf(acc_dom_buffer_t *b) {
    // dump into a file
    char *filename = calloc(1, 64); // not sure how safe 64 is
    sprintf(filename, b->file_format, b->uid, 0);

    FILE* f = fopen(filename, "w");
    int i;
    for(i = 0 ; i < b->dim ; i++) {
      print(&(b->ranges[i]), f);
      fprintf(f, " ");
    }
}

void destroy_subbuf(acc_dom_buffer_t *b) {
  dump_subbuf(b);
  free(b->ranges);
  free(b->file_format);
}

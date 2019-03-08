#ifndef ACC_DOM_BUFFER_H
#define ACC_DOM_BUFFER_H

typedef struct range {
  int low;
  int high;
} range_t;

typedef struct acc_dom_buffer {
  int dim;
  int uid;

  range_t *ranges;

  char *file_format;
} acc_dom_buffer_t;

void init_range(range_t *r);
void expand_range(range_t *r, int idx);
void print(range_t *r, FILE *f);

void init_subbuf(acc_dom_buffer_t *b, int uid, size_t cap, int dim,
                 const char *file_format);
void append_to_subbuf(acc_dom_buffer_t *b, int *dim);
void dump_subbuf(acc_dom_buffer_t *b);
void destroy_subbuf(acc_dom_buffer_t *b);



#endif

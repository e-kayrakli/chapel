#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>

#include "log_buffer.h"
#include "byte_buffer.h"


void init_log_buffer(log_buffer_t *lbuf, uint32_t num_buffers,
                     uint8_t rank, int byte_buf_size, int locale_id,
                     const char *file_prefix) {

  // build the file format string first so that it can be passed to
  // individual byte buffers
  const size_t prefix_len = strlen(file_prefix);
  const size_t full_len = prefix_len + 32; // prolly too conservative
  lbuf->file_format = calloc(full_len, sizeof(char));
  strcpy(lbuf->file_format, file_prefix);
  strcat(lbuf->file_format, "_buf%d_dump%d");

  int i;
  lbuf->num_buffers = num_buffers;
  lbuf->bufs = malloc(num_buffers * sizeof(byte_buffer_t));
  for(i = 0 ; i < num_buffers ; i++) {
    init_byte_buffer(&(lbuf->bufs[i]), i, byte_buf_size,
                     lbuf->file_format);
  }

  lbuf->global_scratch_pad = malloc(num_buffers*SCRATCH_PAD_SIZE);
  lbuf->scratch_pads = malloc(num_buffers*sizeof(char*));
  for(i = 0 ; i < num_buffers ; i++) {
    lbuf->scratch_pads[i] = 
      &lbuf->global_scratch_pad[SCRATCH_PAD_SIZE*i];
  }

  lbuf->cur_buf = 0;
  lbuf->rank = rank;
  lbuf->locale_id = locale_id;

  lbuf->locks = malloc(num_buffers * sizeof(pthread_mutex_t));
  for(i = 0 ; i < num_buffers ; i++) {
    pthread_mutex_init(&(lbuf->locks[i]), NULL);
  }
  /*printf("Inited log buffer %p\n", lbuf);*/
}

int get_compression_stats(log_buffer_t *lbuf,
                          size_t *uncomp_size, size_t *comp_size) {

#ifdef GENERATE_COMPRESSION_STATS
  int i;
  size_t tot_uncomp_size = 0;
  size_t tot_comp_size = 0;

  for(i = 0 ; i < lbuf->num_buffers ; i++) {
    tot_uncomp_size += lbuf->bufs[i].comp_stats.uncomp_size;
    tot_comp_size += lbuf->bufs[i].comp_stats.comp_size;
  }
  *uncomp_size = tot_uncomp_size;
  *comp_size = tot_comp_size;
  return 1;
#else
  return 0;
#endif
}

void destroy_log_buffer(log_buffer_t *lbuf) {
  int i;


  for(i = 0 ; i < lbuf->num_buffers ; i++) {
    destroy_byte_buffer(&(lbuf->bufs[i]));
    pthread_mutex_destroy(&(lbuf->locks[i]));
  }

  free(lbuf->global_scratch_pad);
  /*printf("Destroyed log buffer %p\n", lbuf);*/
}

void append_index(log_buffer_t *lbuf, ...) {

  /*printf("Appending log buffer %p\n", lbuf);*/
  // process varargs
  va_list ap;
  va_start(ap, lbuf->rank);
  int index[lbuf->rank];

  int i;
  for(i = 0 ; i < lbuf->rank ; i++) {
    index[i] = va_arg(ap, int);
  }
  va_end(ap);

  // obtain a buffer -- do a fetchadd and lock
  uint32_t my_buf_idx = __sync_fetch_and_add(&(lbuf->cur_buf), 1);
  my_buf_idx = my_buf_idx % lbuf->num_buffers;

  pthread_mutex_lock(&(lbuf->locks[my_buf_idx]));

  /*printf("Appending %d\n", index[0]);*/

  byte_buffer_t *my_buf = &lbuf->bufs[my_buf_idx];
  char *my_sp = lbuf->scratch_pads[my_buf_idx];

  // create the scratch pad from reverse
  size_t my_sp_off = SCRATCH_PAD_SIZE-1;

  // end with newline
  my_sp[my_sp_off--]='\n';

  for(i = 0 ; i < lbuf->rank ; i++) {
    int digits_added = reverse_itoa(index[i], &my_sp[my_sp_off]);
    my_sp_off -= digits_added;
    if(i != lbuf->rank-1) {
      my_sp[my_sp_off--] = ' ';
    }
  }

  size_t digits = (SCRATCH_PAD_SIZE-1)-my_sp_off;

  append_bytes(my_buf, &my_sp[my_sp_off+1], digits);

  // release the buffer -- unlock the mutex
  pthread_mutex_unlock(&(lbuf->locks[my_buf_idx]));
}

void flush_buffer(log_buffer_t *lbuf) {
  int i;
  for(i = 0 ; i < lbuf->num_buffers ; i++) {
    compress_and_dump(&(lbuf->bufs[i]));
  }
}

#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>

#include "byte_buffer.h"

// in bytes (chars)
#define SCRATCH_PAD_SIZE 32

typedef struct log_buffer {
  uint32_t num_buffers;
  byte_buffer_t *bufs;

  char *global_scratch_pad;
  char **scratch_pads;

  // should be used atomically
  uint32_t cur_buf;

  // info about the indices to be expected
  uint8_t rank;

  pthread_mutex_t *locks;

} log_buffer_t;

void init_log_buffer(log_buffer_t *lbuf, uint32_t num_buffers,
                     uint8_t rank);
void destroy_log_buffer(log_buffer_t *lbuf);
void flush_buffer(log_buffer_t *lbuf);
void append_index(log_buffer_t *lbuf, ...);

#endif

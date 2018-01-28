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

  // log buffers need to know which locale are they so they know where
  // to store the data
  int locale_id;

  // file format string that is partially received from the internal
  // modules and concatanated with _buf%d_dump%d in order to sprintf
  // each time dumping a file
  char *file_format;

  pthread_mutex_t *locks;

} log_buffer_t;

void init_log_buffer(log_buffer_t *lbuf, uint32_t num_buffers,
                     uint8_t rank, int byte_buf_size,
                     int locale_id, const char *file_format);
void destroy_log_buffer(log_buffer_t *lbuf);
void flush_buffer(log_buffer_t *lbuf);
void append_index(log_buffer_t *lbuf, ...);
int get_compression_stats(log_buffer_t *lbuf,
                          size_t *uncomp_size, size_t *comp_size);

#endif

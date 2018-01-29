#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <pthread.h>

#include "byte_buffer.h"
#include "compress.h"

#define IN_DELIM ' '
#define OUT_DELIM '\n'

void init_byte_buffer(byte_buffer_t *buf, int uid, size_t cap, 
                      const char *file_format) {
  buf->uid = uid;
  buf->cuid = calloc(1,32); // deprecated ?
  itoa(buf->uid, buf->cuid);

  buf->data = malloc(cap);
  assert(buf->data);

  buf->cur = buf->data;
  buf->cap = cap;
  buf->size = 0;

  buf->c_size = LZ4F_compressBound(cap, &lz4_preferences) +
                  LZ4_HEADER_SIZE +
                  LZ4_FOOTER_SIZE;
  buf->c_data = malloc(buf->c_size);

  buf->file_count = 0;

  buf->file_format = calloc(strlen(file_format)+4, sizeof(char)); //.lz4

  strcpy(buf->file_format, file_format);
  strcat(buf->file_format, ".lz4");

  /*printf(buf->file_format, 0, 0);*/

  init_compress_stats(&(buf->comp_stats));

#ifdef BYTE_BUFFER_PARSAFE
  pthread_mutex_init(buf->lock, NULL);
#endif
}

static inline void lock(byte_buffer_t *buf) {
#ifdef BYTE_BUFFER_PARSAFE
  pthread_mutex_lock(buf->lock);
#endif
}

static inline void unlock(byte_buffer_t *buf) {
#ifdef BYTE_BUFFER_PARSAFE
  pthread_mutex_unlock(buf->lock);
#endif
}

void compress_and_dump(byte_buffer_t *buf) {
    // compress
    const int compressed_size = compress(buf->data, buf->size,
                                         buf->c_data, buf->c_size,
                                         &(buf->comp_stats));

    // dump into a file
    char *filename = calloc(1, 64); // not sure how safe 64 is
    sprintf(filename, buf->file_format, buf->uid, buf->file_count);

    FILE* f = fopen(filename, "wb");
    size_t written_size = fwrite(buf->c_data, 1, compressed_size, f);
    assert(compressed_size==written_size);
    fclose(f);

    // reset
    buf->cur = buf->data;
    buf->size = 0;
    buf->file_count++;
}

void destroy_byte_buffer(byte_buffer_t *buf) {
  if(buf->size > 0)
    compress_and_dump(buf);

  // TODO reclaim memory?
}

// In current design this is not parallel-safe
static inline void check_cap(byte_buffer_t *buf, size_t incoming) {

  // check if there is still capacity
  if(buf->size + incoming > buf->cap - 1) {
    // if not compress, dump into a file, reset, increment fcounter
    compress_and_dump(buf);
  }
}


void append_byte(byte_buffer_t *buf, const char byte) {

  lock(buf);
  check_cap(buf, 1);
  
  memcpy(buf->cur, &byte, 1);
  buf->size += 1;
  buf->cur += 1;
  unlock(buf);
}

void append_bytes(byte_buffer_t *buf, char *bytes, int num_bytes) {

  lock(buf);
  check_cap(buf, num_bytes);

  memcpy(buf->cur, bytes, num_bytes);
  buf->size += num_bytes;
  buf->cur += num_bytes;

  unlock(buf);
}

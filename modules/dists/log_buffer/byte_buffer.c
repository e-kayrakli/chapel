
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <pthread.h>

#include "byte_buffer.h"

#define IN_DELIM ' '
#define OUT_DELIM '\n'

void init_byte_buffer(byte_buffer_t *buf, int uid, size_t cap) {
  buf->uid = uid;
  buf->cuid = calloc(1,32);
  itoa(buf->uid, buf->cuid);

  buf->data = malloc(cap);
  assert(buf->data);

  buf->cur = buf->data;
  buf->cap = cap;
  buf->size = 0;

  buf->max_c_sz = LZ4F_compressBound(cap, &lz4_preferences) +
                  LZ4_HEADER_SIZE +
                  LZ4_FOOTER_SIZE;
  buf->c_data = malloc(buf->max_c_sz);

  buf->file_count = 0;

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

void check_err(size_t code, const char* msg) {
  if(LZ4F_isError(code)) {
    fprintf(stderr, msg);
    exit(1);
  }
}

size_t compress(byte_buffer_t *buf) {
  // create the compression context
  LZ4F_compressionContext_t ctx;
  LZ4F_createCompressionContext(&ctx, LZ4F_VERSION);

  size_t comp_off = 0;

  // generate frame header (?)
  size_t header_size = LZ4F_compressBegin(ctx, buf->c_data,
                                          buf->max_c_sz,
                                          &lz4_preferences);

  check_err(header_size, "Cannot begin compression\n");
  comp_off += header_size;

  // compress the actual data
  size_t data_size = LZ4F_compressUpdate(ctx,
                                         buf->c_data + comp_off, 
                                         buf->max_c_sz - comp_off,
                                         buf->data, buf->size,
                                         NULL);

  check_err(data_size, "Cannot update compression\n");
  comp_off += data_size;

  // end the frame
  size_t footer_size = LZ4F_compressEnd(ctx,
                                        buf->c_data + comp_off, 
                                        buf->max_c_sz - comp_off,
                                        NULL);

  check_err(footer_size , "Cannot end compression\n");
  comp_off += footer_size;

  LZ4F_freeCompressionContext(ctx);
  return comp_off;
}


void compress_and_dump(byte_buffer_t *buf) {
    // compress
    const int compressed_size = compress(buf);

    // dump into a file
    char *filename = calloc(1, 32);
    itoa(buf->file_count, filename);
    strcat(filename, buf->cuid);
    strcat(filename, ".lz4");

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
  compress_and_dump(buf);
}

// In current design this is not parallel-safe
void check_cap(byte_buffer_t *buf, size_t incoming) {

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

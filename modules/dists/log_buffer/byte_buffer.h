#ifndef BYTE_BUFFER_H
#define BYTE_BUFFER_H

#include <pthread.h>

#include "lz4frame.h"

#define LZ4_HEADER_SIZE 19
#define LZ4_FOOTER_SIZE 4


// this is not parallel-safe
typedef struct byte_buffer {
  int uid;
  char *cuid;

  char *data;

  char *cur;
  size_t cap;
  size_t size;

  // so that we don't reallocate everytime we dump
  char *c_data;
  size_t max_c_sz;

  int file_count;

  pthread_mutex_t *lock;
} byte_buffer_t;

void init_byte_buffer(byte_buffer_t *buf, int uid, size_t cap);
void destroy_byte_buffer(byte_buffer_t *buf);
void compress_and_dump(byte_buffer_t *buf);
void append_byte(byte_buffer_t *buf, const char byte);
void append_bytes(byte_buffer_t *buf, char *bytes, int num_bytes);

static const LZ4F_preferences_t lz4_preferences = {
    { LZ4F_max256KB, LZ4F_blockLinked, LZ4F_noContentChecksum, LZ4F_frame,
      0 /* content size unknown */, 0 /* no dictID */ , LZ4F_noBlockChecksum },
    0,   /* compression level */
    0,   /* autoflush */
    { 0, 0, 0, 0 },  /* reserved, must be set to 0 */
};

// This doesn't do any size-checking. Buyer beware
static inline int itoa(int ind, char *out) {

  // TODO get rid of this log10
  int num_digits = ind ? log10(ind)+1 : 1;

  int cnt = num_digits-1;
  do {
    out[cnt] = '0' + (ind % 10);
    ind /= 10;
    cnt -= 1;
  } while (ind>0);

  return num_digits;
}

// sp_end will be the lsd of the input
static inline int reverse_itoa(int i, char *sp_end) {

  char *cur = sp_end;
  int count = 0;
  do {
    *cur = '0' + (i % 10);
    i /= 10;
    cur -= 1;
    count++;
  } while (i>0);

  return count;

}
#endif

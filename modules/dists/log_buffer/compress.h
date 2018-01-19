#ifndef COMPRESS_H
#define COMPRESS_H


typedef struct compress_stats {
  size_t uncomp_size;
  size_t comp_size;
} compress_stats_t;

void init_compress_stats(compress_stats_t *stats);
size_t compress(char *in_data, size_t in_size, 
                char *out_data, size_t out_size, 
                compress_stats_t *stats);



static const LZ4F_preferences_t lz4_preferences = {
  { 
    LZ4F_max256KB,
    LZ4F_blockLinked, 
    LZ4F_noContentChecksum, 
    LZ4F_frame,
    0 /* content size unknown */,
    0 /* no dictID */ ,
    LZ4F_noBlockChecksum 
  },
  0,   /* compression level */
  0,   /* autoflush */
  { 0, 0, 0, 0 },  /* reserved, must be set to 0 */
};
#endif

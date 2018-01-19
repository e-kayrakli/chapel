#include <stdio.h>
#include <stdlib.h>

#include "lz4frame.h"
#include "compress.h"

/*#define GENERATE_COMPRESSION_STATS 0*/

void init_compress_stats(compress_stats_t *stats) {
  stats->uncomp_size = 0;
  stats->comp_size = 0;
}

void check_err(size_t code, const char* msg) {
  if(LZ4F_isError(code)) {
    fprintf(stderr, msg);
    exit(1);
  }
}

size_t compress(char *in_data, size_t in_size, 
                char *out_data, size_t out_size, 
                compress_stats_t *stats) {
  // create the compression context
#ifdef GENERATE_COMPRESSION_STATS
  stats->uncomp_size += in_size;
  /*printf("insize : %d\n", in_size);*/
  /*printf("stats->uncomp_size : %d\n", stats->uncomp_size);*/
  /*printf("stats : %p\n", stats);*/
#endif
  LZ4F_compressionContext_t ctx;
  LZ4F_createCompressionContext(&ctx, LZ4F_VERSION);

  size_t comp_off = 0;

  // generate frame header (?)
  /*size_t header_size = LZ4F_compressBegin(ctx, buf->c_data,*/
                                          /*buf->max_c_sz,*/
                                          /*&lz4_preferences);*/
  size_t header_size = LZ4F_compressBegin(ctx, out_data, out_size,
                                          &lz4_preferences);

  check_err(header_size, "Cannot begin compression\n");
  comp_off += header_size;

  // compress the actual data
  /*size_t data_size = LZ4F_compressUpdate(ctx,*/
                                         /*buf->c_data + comp_off, */
                                         /*buf->max_c_sz - comp_off,*/
                                         /*buf->data, buf->size,*/
                                         /*NULL);*/

  size_t data_size = LZ4F_compressUpdate(ctx,
                                         out_data + comp_off, 
                                         out_size - comp_off,
                                         in_data, in_size,
                                         NULL);
  check_err(data_size, "Cannot update compression\n");
  comp_off += data_size;

  // end the frame
  /*size_t footer_size = LZ4F_compressEnd(ctx,*/
                                        /*buf->c_data + comp_off, */
                                        /*buf->max_c_sz - comp_off,*/
                                        /*NULL);*/
  size_t footer_size = LZ4F_compressEnd(ctx,
                                        out_data + comp_off, 
                                        out_size - comp_off,
                                        NULL);

  check_err(footer_size , "Cannot end compression\n");
  comp_off += footer_size;

  LZ4F_freeCompressionContext(ctx);

#ifdef GENERATE_COMPRESSION_STATS
  stats->comp_size += comp_off;
#endif
  return comp_off;
}

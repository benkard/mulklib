#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef BPT_KEY_T         bpt_key_t;
typedef BPT_KEY_BITMASK_T bpt_key_bitmask_t;

int main() {
  long chunk_length = (int)log2(sizeof(bpt_key_bitmask_t)*8);
  long key_length   = sizeof(bpt_key_t)*8;
  long offset_mask  = ((1 << chunk_length) - 1);
  long max_chunks   = key_length / chunk_length + ((key_length % chunk_length == 0) ? 0 : 1);
  long last_chunk_length = key_length - ((max_chunks - 1) * chunk_length);
  printf("-DCHUNK_LENGTH=%ld -DKEY_LENGTH=%ld -DOFFSET_MASK=%ld -DMAX_CHUNKS=%ld -DLAST_CHUNK_LENGTH=%ld",
         chunk_length, key_length, offset_mask, max_chunks, last_chunk_length);
  return EXIT_SUCCESS;
}


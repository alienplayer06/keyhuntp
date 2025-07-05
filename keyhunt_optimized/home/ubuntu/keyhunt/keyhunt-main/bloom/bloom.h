#include <cstdint>
#ifndef _BLOOM_H
#define _BLOOM_H

#ifdef _WIN64
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/** ***************************************************************************
 * Structure to keep track of one bloom filter.  Caller needs to
 * allocate this and pass it to the functions below. First call for
 * every struct must be to bloom_init().
 *
 */
struct bloom
{
  // These fields are part of the public interface of this structure.
  // Client code may read these values if desired. Client code MUST NOT
  // modify any of these.
  uint64_t entries;
  uint64_t bits;
  uint64_t bytes;
  uint8_t hashes;
  long double error;

  // Fields below are private to the implementation. These may go away or
  // change incompatibly at any moment. Client code MUST NOT access or rely
  // on these.
  uint8_t ready;
  uint8_t major;
  uint8_t minor;
  double bpe;
  uint8_t *bf;
};

int bloom_init2(struct bloom * bloom, uint64_t entries, long double error);
int bloom_init(struct bloom * bloom, uint64_t entries, long double error);
int bloom_check(struct bloom * bloom, const void * buffer, int len);
int bloom_add(struct bloom * bloom, const void * buffer, int len);
void bloom_print(struct bloom * bloom);
void bloom_free(struct bloom * bloom);
int bloom_reset(struct bloom * bloom);
const char * bloom_version();

// New functions for RMD160
int bloom_add_rmd160(struct bloom * bloom, const unsigned char * rmd160_hash);
int bloom_check_rmd160(struct bloom * bloom, const unsigned char * rmd160_hash);


#ifdef __cplusplus
}
#endif

#endif


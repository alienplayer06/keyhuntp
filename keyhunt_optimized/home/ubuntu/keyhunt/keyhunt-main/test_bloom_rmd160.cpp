#include <stdio.h>
#include <string.h>
#include "bloom/bloom.h"
#include "hash/ripemd160.h"

int main() {
    struct bloom mybloom;
    bloom_init2(&mybloom, 1000000, 0.0001);

    unsigned char hash1[20];
    CRIPEMD160 rmd160_hasher1;
    const char* test_string1 = "hello world";
    rmd160_hasher1.Write((const unsigned char*)test_string1, strlen(test_string1));
    rmd160_hasher1.Finalize(hash1);

    unsigned char hash2[20];
    CRIPEMD160 rmd160_hasher2;
    const char* test_string2 = "hello world again";
    rmd160_hasher2.Write((const unsigned char*)test_string2, strlen(test_string2));
    rmd160_hasher2.Finalize(hash2);

    // Add hash1 to the bloom filter
    int add_result = bloom_add_rmd160(&mybloom, hash1);
    if (add_result == 0) {
        printf("Hash1 added to bloom filter.\n");
    } else if (add_result == 1) {
        printf("Hash1 already in bloom filter (or collision).\n");
    } else {
        printf("Error adding Hash1 to bloom filter.\n");
    }

    // Check for hash1 in the bloom filter
    int check_result1 = bloom_check_rmd160(&mybloom, hash1);
    if (check_result1 == 1) {
        printf("Hash1 found in bloom filter.\n");
    } else if (check_result1 == 0) {
        printf("Hash1 not found in bloom filter.\n");
    } else {
        printf("Error checking Hash1 in bloom filter.\n");
    }

    // Check for hash2 in the bloom filter
    int check_result2 = bloom_check_rmd160(&mybloom, hash2);
    if (check_result2 == 1) {
        printf("Hash2 found in bloom filter.\n");
    } else if (check_result2 == 0) {
        printf("Hash2 not found in bloom filter.\n");
    } else {
        printf("Error checking Hash2 in bloom filter.\n");
    }

    bloom_free(&mybloom);
    return 0;
}


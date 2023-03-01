#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_BLOCK_SIZE 1024

void generate_block_hash(char* block_data, int block_size, unsigned char* hash)
{
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, block_data, block_size);
    SHA256_Final(hash, &ctx);
}

int verify_block(char* block_data, int block_size, unsigned char* prev_hash, unsigned char* block_hash)
{
    unsigned char computed_hash[SHA256_DIGEST_LENGTH];
    generate_block_hash(block_data, block_size, computed_hash);

    if (memcmp(computed_hash, block_hash, SHA256_DIGEST_LENGTH) != 0)
    {
        return 0; // Block hash does not match computed hash
    }

    if (memcmp(prev_hash, block_hash, SHA256_DIGEST_LENGTH) != 0)
    {
        return 0; // Previous hash does not match current block hash
    }

    return 1; // Block is valid
}

int main()
{
    char block_data[MAX_BLOCK_SIZE] = "This is a sample block of data";
    int block_size = strlen(block_data);
    unsigned char prev_hash[SHA256_DIGEST_LENGTH] = {0x1a, 0x2b, 0x3c, 0x4d, 0x5e, 0x6f, 0x7a, 0x8b, 0x9c, 0xad};
    unsigned char block_hash[SHA256_DIGEST_LENGTH] = {0};

    generate_block_hash(block_data, block_size, block_hash);

    if (verify_block(block_data, block_size, prev_hash, block_hash))
    {
        printf("Block is valid.\n");
    }
    else
    {
        printf("Block is invalid.\n");
    }

    return 0;
}
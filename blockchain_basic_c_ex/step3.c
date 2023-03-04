/*
gcc -o s3 step3.c -lssl -lcrypto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_BLOCK_SIZE 1024
#define MAX_CHAIN_LENGTH 10

typedef struct
{
    char data[MAX_BLOCK_SIZE];
    int size;
    unsigned char hash[SHA256_DIGEST_LENGTH];
} block_t;

block_t blockchain[MAX_CHAIN_LENGTH];
int chain_length = 0;

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

int verify_chain()
{
    for (int i = 1; i < chain_length; i++)
    {
        if (!verify_block(blockchain[i].data, blockchain[i].size, blockchain[i - 1].hash, blockchain[i].hash))
        {
            return 0; // Chain is invalid
        }
    }

    return 1; // Chain is valid
}

int add_block(char* block_data, int block_size)
{
    if (chain_length == MAX_CHAIN_LENGTH)
    {
        return 0; // Chain is full
    }

    block_t* new_block = &blockchain[chain_length];
    strncpy(new_block->data, block_data, block_size);
    new_block->size = block_size;

    if (chain_length == 0)
    {
        // First block in the chain
        unsigned char null_hash[SHA256_DIGEST_LENGTH] = {0};
        generate_block_hash(new_block->data, new_block->size, new_block->hash);
        memcpy(blockchain[0].hash, null_hash, SHA256_DIGEST_LENGTH);
    }
    else
    {
        // Subsequent blocks in the chain
        generate_block_hash(new_block->data, new_block->size, new_block->hash);
        memcpy(blockchain[chain_length].hash, blockchain[chain_length - 1].hash, SHA256_DIGEST_LENGTH);
    }

    chain_length++;
    return 1; // Block added successfully
}

int main()
{
    add_block("This is the first block of data.", strlen("This is the first block of data."));
    add_block("This is the second block of data.", strlen("This is the second block of data."));
    add_block("This is the third block of data.", strlen("This is the third block of data."));

    printf("Chain length: %d\n", chain_length);

    if (verify_chain())
    {
        printf("Chain is valid.\n");
    }
    else
    {
        printf("Chain is invalid.\n");
    }

    return 0;
}
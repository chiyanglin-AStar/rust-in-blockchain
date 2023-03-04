/*
gcc -o s1 step1.c -lssl -lcrypto
*/
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

int main()
{
    char block_data[MAX_BLOCK_SIZE] = "This is a sample block of data";
    int block_size = strlen(block_data);
    unsigned char block_hash[SHA256_DIGEST_LENGTH];

    generate_block_hash(block_data, block_size, block_hash);

    printf("Block Data: %s\n", block_data);
    printf("Block Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02x", block_hash[i]);
    }
    printf("\n");

    return 0;
}
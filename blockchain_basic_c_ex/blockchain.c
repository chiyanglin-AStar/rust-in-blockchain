#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define BLOCK_DATA_SIZE 1024
#define HASH_LENGTH SHA256_DIGEST_LENGTH

typedef struct Block {
    unsigned int index;
    unsigned char previous_hash[HASH_LENGTH];
    char data[BLOCK_DATA_SIZE];
    unsigned long timestamp;
    unsigned char hash[HASH_LENGTH];
} Block;

typedef struct Blockchain {
    Block *chain;
    unsigned int size;
} Blockchain;

void print_hash(unsigned char hash[HASH_LENGTH]) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void calculate_hash(Block *block, unsigned char *hash) {
    unsigned char data[BLOCK_DATA_SIZE + HASH_LENGTH + 8];
    memcpy(data, &block->index, sizeof(unsigned int));
    memcpy(data + sizeof(unsigned int), block->previous_hash, HASH_LENGTH);
    memcpy(data + sizeof(unsigned int) + HASH_LENGTH, block->data, BLOCK_DATA_SIZE);
    memcpy(data + sizeof(unsigned int) + HASH_LENGTH + BLOCK_DATA_SIZE, &block->timestamp, sizeof(unsigned long));

    SHA256(data, sizeof(data), hash);
}

Blockchain* create_blockchain() {
    Blockchain *bc = malloc(sizeof(Blockchain));
    bc->size = 0;
    bc->chain = NULL;
    return bc;
}

void add_block(Blockchain *bc, char *data) {
    Block *block = malloc(sizeof(Block));
    block->index = bc->size;
    memcpy(block->previous_hash, bc->chain[bc->size - 1].hash, HASH_LENGTH);
    memcpy(block->data, data, strlen(data));
    block->timestamp = time(NULL);
    calculate_hash(block, block->hash);

    bc->chain = realloc(bc->chain, (bc->size + 1) * sizeof(Block));
    bc->chain[bc->size] = *block;
    bc->size++;
}

int is_valid_block(Block *block, Block *previous_block) {
    if (block->index != previous_block->index + 1) {
        return 0;
    }

    if (memcmp(block->previous_hash, previous_block->hash, HASH_LENGTH) != 0) {
        return 0;
    }

    unsigned char hash[HASH_LENGTH];
    calculate_hash(block, hash);
    if (memcmp(block->hash, hash, HASH_LENGTH) != 0) {
        return 0;
    }

    return 1;
}

int is_valid_blockchain(Blockchain *bc) {
    for (int i = 1; i < bc->size; i++) {
        if (!is_valid_block(&bc->chain[i], &bc->chain[i - 1])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    Blockchain *bc = create_blockchain();

    // Add genesis block
    Block *genesis_block = malloc(sizeof(Block));
    genesis_block->index = 0;
    memset(genesis_block->previous_hash, 0, HASH_LENGTH);
    memcpy(genesis_block->data, "Hello, world!", 14);
    genesis_block->timestamp = time(NULL);
    calculate_hash(genesis_block, genesis_block->hash);
    bc->chain = malloc(sizeof(Block));
    bc->chain[0] = *genesis_block;
    bc->size++;

    // Add some more blocks
    add_block(bc, "This is the second block.");
    add_block(bc, "This is the third block.");
    add_block(bc, "This is the fourth block.");
    add_block(bc, "This is the fifth block.");
    add_block(bc, "This is the sixth block.");
}
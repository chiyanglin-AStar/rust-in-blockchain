#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void mine(int block_number, char *transactions, char *previous_hash, int difficulty) {
    unsigned int nonce = 0;
    char block_data[1024];
    char block_hash[65];

    while (1) {
        sprintf(block_data, "%d%s%s%u", block_number, transactions, previous_hash, nonce);
        SHA256(block_data, strlen(block_data), block_hash);

        if (strncmp(block_hash, "0000000000000000", difficulty) == 0) {
            printf("Block mined! Nonce: %u, Hash: %s\n", nonce, block_hash);
            return;
        }

        nonce++;
    }
}

int main() {
    int block_number = 12345;
    char *transactions = "Transaction data...";
    char *previous_hash = "0000000000000000000000000000000000000000000000000000000000000000";
    int difficulty = 5;

    mine(block_number, transactions, previous_hash, difficulty);

    return 0;
}
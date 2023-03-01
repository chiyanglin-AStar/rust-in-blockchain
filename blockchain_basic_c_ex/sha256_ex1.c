/*
gcc -o sha256 sha256.c -lssl -lcrypto
*/
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
int main() {
    char message[] = "Hello, world!";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(message, strlen(message), hash);

    printf("Message: %s\n", message);
    printf("Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
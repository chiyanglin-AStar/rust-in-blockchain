/*
gcc -o sha256file sha256_ex2.c -lssl -lcrypto

./sha256file <filename>

*/

#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    unsigned char *buffer = malloc(filesize);
    if (!buffer) {
        fprintf(stderr, "Error: could not allocate memory\n");
        return 1;
    }

    size_t result = fread(buffer, 1, filesize, file);
    if (result != filesize) {
        fprintf(stderr, "Error: could not read file %s\n", filename);
        return 1;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(buffer, filesize, hash);

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", filesize);
    printf("Hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    free(buffer);
    fclose(file);
    return 0;
}
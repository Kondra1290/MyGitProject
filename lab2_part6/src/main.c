#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hasher.h"
int main() {
    char input[1024];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    printf("Enter a string to hash: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    input[strcspn(input, "\n")] = 0;
    sha256(input, hash);
    printf("SHA-256 hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    return 0;
}

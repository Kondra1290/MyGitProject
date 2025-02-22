#ifndef HASHER_H
#define HASHER_H
#include <openssl/sha.h>
void sha256(const char *str, unsigned char *output);
#endif // HASHER_H

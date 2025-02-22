#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
static int (*real_unlink)(const char *pathname) = NULL;
int unlink(const char *pathname) {
    if (!real_unlink) {
        real_unlink = dlsym(RTLD_NEXT, "unlink");
    }
    if (strstr(pathname, "PROTECT") != NULL) {
        fprintf(stderr, "Attempt to delete protected file: %s\n", pathname);
        return -1; 
    }
    return real_unlink(pathname);
}

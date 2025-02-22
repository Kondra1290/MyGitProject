#include <stdio.h>
#include <stdlib.h>
int main() {
    const char *protected_file = "PROTECT_me.txt";
    FILE *file = fopen(protected_file, "w");
    if (!file) {
        perror("Failed to create protected file");
        return EXIT_FAILURE;
    }
    fclose(file);
    if (unlink(protected_file) == 0) {
        printf("File %s deleted successfully, which is unexpected!\n", protected_file);
        return EXIT_FAILURE;
    } else {
        printf("File %s could not be deleted as expected.\n", protected_file);
    }
    return EXIT_SUCCESS;
}

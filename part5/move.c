#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUFFER_SIZE 1024
void print_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];
    int src_fd = open(infile, O_RDONLY);
    if (src_fd < 0) {
        print_error("Error opening input file");
    }
    int dest_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        close(src_fd);
        print_error("Error opening output file");
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            close(src_fd);
            close(dest_fd);
            print_error("Error writing to output file");
        }
    }
    if (bytes_read < 0) {
        close(src_fd);
        close(dest_fd);
        print_error("Error reading from input file");
    }
    if (close(dest_fd) < 0) {
        close(src_fd);
        print_error("Error closing output file");
    }
    if (close(src_fd) < 0) {
        print_error("Error closing input file");
    }
    if (remove(infile) < 0) {
        print_error("Error deleting input file");
    }
    return EXIT_SUCCESS;
}

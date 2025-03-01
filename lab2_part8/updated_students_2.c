#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "hasher.h"

struct Student {
    int id;
    char name[50];
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Хранение хэша имени
};

// Функция вычисления хэша имени
void computeStudentHash(struct Student *student) {
    sha256(student->name, student->hash);
}

// Функция вывода студентов
void printStudents(struct Student students[], int count) {
    printf("List of students:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Hash: ", students[i].id, students[i].name);
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
            printf("%02x", students[i].hash[j]);
        }
        printf("\n");
    }
}

// Функция поиска студента по ID
void findStudentById(struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Student found: ID: %d, Name: %s, Hash: ", students[i].id, students[i].name);
            for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
                printf("%02x", students[i].hash[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

int main() {
    struct Student students[3] = {
        {1, "John Doe"},
        {2, "Jane Smith"},
        {3, "Alice Johnson"}
    };

    // Вычисляем хэши имен студентов
    for (int i = 0; i < 3; i++) {
        computeStudentHash(&students[i]);
    }

    printStudents(students, 3);

    int searchId;
    printf("Enter student ID to search: ");
    scanf("%d", &searchId);
    findStudentById(students, 3, searchId);

    return 0;
}

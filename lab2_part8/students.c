#include <stdio.h>
struct Student {
    int id;
    char name[50];
};
void printStudents(struct Student students[], int count) {
    printf("List of students:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s\n", students[i].id, students[i].name);
    }
}
void findStudentById(struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Student found: ID: %d, Name: %s\n", students[i].id, students[i].name);
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
    printStudents(students, 3);
    int searchId;
    printf("Enter student ID to search: ");
    scanf("%d", &searchId);
    findStudentById(students, 3, searchId);
    return 0;
}

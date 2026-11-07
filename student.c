#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

int main(void) {
    struct Student s;
    int choice, searchId, found;
    FILE *fp;

    while (1) {
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            fp = fopen("students.dat", "ab");
            if (fp == NULL) {
                printf("File error!\n");
                continue;
            }

            printf("Enter ID: ");
            scanf("%d", &s.id);
            printf("Enter Name (no spaces): ");
            scanf("%49s", s.name);
            printf("Enter Marks: ");
            scanf("%f", &s.marks);

            fwrite(&s, sizeof(s), 1, fp);
            fclose(fp);
            printf("Student added!\n");
        }
        else if (choice == 2) {
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("No records found!\n");
                continue;
            }

            printf("\nID\tName\tMarks\n");
            while (fread(&s, sizeof(s), 1, fp) == 1) {
                printf("%d\t%s\t%.2f\n", s.id, s.name, s.marks);
            }
            fclose(fp);
        }
        else if (choice == 3) {
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("No records found!\n");
                continue;
            }

            printf("Enter ID to search: ");
            scanf("%d", &searchId);
            found = 0;

            while (fread(&s, sizeof(s), 1, fp) == 1) {
                if (s.id == searchId) {
                    printf("ID: %d\n", s.id);
                    printf("Name: %s\n", s.name);
                    printf("Marks: %.2f\n", s.marks);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Student not found!\n");
            }
            fclose(fp);
        }
        else if (choice == 4) {
            printf("Thank you!\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

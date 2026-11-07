#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

int main(void) {
    struct Student s;
    int choice, id, found;
    FILE *fp, *temp;

    while (1) {
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            return 1;
        }

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
            printf("Student added successfully!\n");
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
            scanf("%d", &id);
            found = 0;

            while (fread(&s, sizeof(s), 1, fp) == 1) {
                if (s.id == id) {
                    printf("ID: %d\nName: %s\nMarks: %.2f\n",
                           s.id, s.name, s.marks);
                    found = 1;
                    break;
                }
            }

            if (!found)
                printf("Student not found!\n");

            fclose(fp);
        }

        else if (choice == 4 || choice == 5) {
            fp = fopen("students.dat", "rb");
            if (fp == NULL) {
                printf("No records found!\n");
                continue;
            }

            temp = fopen("temp.dat", "wb");
            if (temp == NULL) {
                fclose(fp);
                printf("File error!\n");
                continue;
            }

            printf("Enter Student ID: ");
            scanf("%d", &id);
            found = 0;

            while (fread(&s, sizeof(s), 1, fp) == 1) {
                if (s.id == id && !found) {
                    found = 1;

                    if (choice == 4) {
                        printf("Enter New Name (no spaces): ");
                        scanf("%49s", s.name);
                        printf("Enter New Marks: ");
                        scanf("%f", &s.marks);
                        fwrite(&s, sizeof(s), 1, temp);
                    }
                } else {
                    fwrite(&s, sizeof(s), 1, temp);
                }
            }

            fclose(fp);
            fclose(temp);

            if (found) {
                remove("students.dat");
                rename("temp.dat", "students.dat");

                if (choice == 4)
                    printf("Student updated successfully!\n");
                else
                    printf("Student deleted successfully!\n");
            } else {
                remove("temp.dat");
                printf("Student not found!\n");
            }
        }

        else if (choice == 6) {
            printf("Thank you!\n");
            break;
        }

        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}


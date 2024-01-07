#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        printf("File %s already exists. Choose a different name.\n", filename);
        fclose(file);
    } else {
        file = fopen(filename, "w");
        printf("File %s created successfully.\n", filename);
        fclose(file);
    }
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File %s deleted successfully.\n", filename);
    } else {
        printf("Error deleting file %s.\n", filename);
    }
}

void duplicateFile(const char *srcFilename, const char *destFilename) {
    FILE *srcFile = fopen(srcFilename, "rb");
    FILE *destFile = fopen(destFilename, "wb");

    if (!srcFile || !destFile) {
        printf("Error opening files for duplication.\n");
        return;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
    printf("File %s duplicated to %s successfully.\n", srcFilename, destFilename);
}

void moveFile(const char *srcFilename, const char *destFilename) {
    if (rename(srcFilename, destFilename) == 0) {
        printf("File %s moved to %s successfully.\n", srcFilename, destFilename);
    } else {
        printf("Error moving file %s.\n", srcFilename);
    }
}

void listFiles(const char *dirPath) {
    printf("Files in directory %s:\n", dirPath);
    system("ls -l");
}

void searchFile(const char *dirPath, const char *filename) {
    char command[1024];
    snprintf(command, sizeof(command), "find %s -name \"%s\"", dirPath, filename);
    printf("Search results for file %s:\n", filename);
    system(command);
}

int main() {
    char filename[256];
    char destFilename[256];
    char dirPath[256];

    printf("Enter directory path: ");
    fgets(dirPath, sizeof(dirPath), stdin);
    dirPath[strcspn(dirPath, "\n")] = '\0'; // Remove newline character

    int choice;
    do {
        printf("\nFile Manager Menu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Duplicate File\n");
        printf("4. Move File\n");
        printf("5. List Files in Directory\n");
        printf("6. Search File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character from previous input

        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                createFile(filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                deleteFile(filename);
                break;
            case 3:
                printf("Enter source filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                printf("Enter destination filename: ");
                fgets(destFilename, sizeof(destFilename), stdin);
                destFilename[strcspn(destFilename, "\n")] = '\0';
                duplicateFile(filename, destFilename);
                break;
            case 4:
                printf("Enter source filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                printf("Enter destination filename: ");
                fgets(destFilename, sizeof(destFilename), stdin);
                destFilename[strcspn(destFilename, "\n")] = '\0';
                moveFile(filename, destFilename);
                break;
            case 5:
                listFiles(dirPath);
                break;
            case 6:
                printf("Enter filename to search: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                searchFile(dirPath, filename);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

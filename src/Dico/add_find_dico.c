#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define ERR(msg) printf("Error in patricia_compress.c/%s: %s\n", __func__, msg)
#define LINE_SIZE 256

void* add_dico_from_file(FILE* fp, void* dico, void* (*dico_add)(char*, void*)) {
    char line[LINE_SIZE];  // Max line size (to be adjusted as needed)

    // Check if input are valid
    if (fp == NULL) {
        ERR("File pointer is NULL\n");
        return NULL;
    }

    if (dico == NULL) {
        ERR("dico = NULL\n");
        return NULL;
    }

    if (dico_add == NULL) {
        ERR("dico_add = NULL\n");
        return NULL;
    }

    // Read and process each line of the file
    while (fgets(line, sizeof(line), fp)) {
        // Check if the line was truncated (absence of '\n' in the buffer and not at EOF)
        if (line[strlen(line) - 1] != '\n' && !feof(fp)) {
            fprintf(stderr, "Line too long, it was truncated: %s\n", line);
            // Ignore the rest of the line if it is too long
            int ch;
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);  // Read until end of line
        }

        // Call the callback function to add the line to the dictionary
        void* result = dico_add(line, dico);
        if (result == NULL) {
            ERR("Failed to add to dictionary\n");
            return NULL;
        }
        dico = result; // Update dictionary if needed

        // Optionally display the processed line
        printf("%s", line);
    }

    // Check if there was an error reading
    if (ferror(fp)) {
        ERR("Error while reading the file\n");
        return NULL;
    }

    return dico; // Return the updated dictionary
}

int find_str_in_dico(const char* str, void* dico, int (*dico_find)(const char*, void*)) {
    // Create a buffer with a fixed size of 256 characters
    char buffer[256];

    if (str == NULL) {
        ERR("str = NULL");
        return -1;
    }

    if (dico == NULL) {
        ERR("dico = NULL");
        return -2; 
    }

    if (dico_find == NULL) {
        ERR("dico_find = NULL");
        return -2; 
    }

    size_t str_len = strlen(str);
    if (str_len >= sizeof(buffer)) {
        ERR("Input string is too long and will be truncated");
        strncpy(buffer, str, sizeof(buffer) - 1); // Copy with truncation
        buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination
    } else {
        strcpy(buffer, str); // Safe to copy
    }

    // Call the function to search in the dictionary
    if (dico_find(buffer, dico) == 1) {
        printf("String found in the dictionary: %s\n", buffer);
        return 1; // Indicates that the string was found
    } else {
        printf("String not found in the dictionary: %s\n", buffer);
        return 0; // Indicates that the string was not found
    }
}

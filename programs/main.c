#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dico_utils.h"

#define ERR(msg) fprintf(stderr, "Error in main.c: %s\n", msg)

int main(int argc, char* argv[]) {

    // Ensure correct number of arguments
    if (argc != 3) {
        ERR("Usage: ./dico dico.txt -a|-h|-tt|-tp|-ttc|ttp (choose one option)");
        return -1;
    }

    // Open the dictionary file
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        ERR("Failed to open the dictionary file");
        return -2;
    }

    // Declare pointers for dictionary data structure and function pointers
    void* dico = NULL;
    int (*dico_find)(char*, void*) = NULL;
    void* (*dico_delete)(void*) = NULL;

    // Determine which dictionary mode to use based on argv[2]
    if (strcmp(argv[2], "-a") == 0) {
        printf("Array mode not yet implemented\n");
    } else if (strcmp(argv[2], "-h") == 0) {
        dico = (void*)hash_dico_controler(fp);  // Cast to void* for generic use
        dico_find = (int (*)(char*, void*))hash_dico_find;  // Cast the function pointer
        dico_delete = (void* (*)(void*))hash_dico_delete;  // Cast the function pointer
    } else if (strcmp(argv[2], "-tt") == 0) {
        dico = (void*)tree_trie_controler(fp);
        dico_find = (int (*)(char*, void*))tree_trie_find;
        dico_delete = (void* (*)(void*))tree_trie_dico_delete;
    } else if (strcmp(argv[2], "-tp") == 0) {
        dico = (void*)tree_patricia_controler(fp);
        dico_find = (int (*)(char*, void*))tree_patricia_find;
        dico_delete = (void* (*)(void*))tree_patricia_dico_delete;
    } else if (strcmp(argv[2], "-ttc") == 0) {
        dico = (void*)trie_compressed_controler(fp);
        dico_find = (int (*)(char*, void*))trie_compressed_find;
        dico_delete = (void* (*)(void*))trie_compressed_dico_delete;
    } else if (strcmp(argv[2], "-ttp") == 0) {
        dico = (void*)patrica_compressed_dico_new(fp);
        dico_find = (int (*)(char*, void*))patrica_compressed_dico_find;
        dico_delete = (void* (*)(void*))patricia_compressed_dico_delete;
    } else {
        ERR("Invalid option, use -a|-h|-tt|-tp|-ttc|-ttp");
        fclose(fp);
        return -1;
    }

    // Validate dictionary and function pointers
    if (dico == NULL || dico_find == NULL || dico_delete == NULL) {
        ERR("Dico initialization or function pointers failed");
        printf("dico = %p, dico_find = %p, dico_delete = %p\n", (void*)dico, dico_find, dico_delete);
        if (dico != NULL) {
            dico = dico_delete(dico);  // Clean up memory in case of error
        }
        fclose(fp);
        return -3;
    }

    // User input loop
    char buffer[256] = "";
    while (strcmp(buffer, "END") != 0) {
        printf("Enter a string (type 'END' to stop): ");
        
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

            if (strcmp(buffer, "END") == 0) {
                break;
            }

            // Call the dictionary find function
            if (dico_find == NULL) {
                ERR("dico find = NULL");
                return -4;
            }
            if (dico_find(buffer, dico) == 1) {
                printf("String found in the dictionary: %s\n", buffer);
            } else {
                printf("String not found in the dictionary: %s\n", buffer);
            }
        } else {
            printf("Error reading input\n");
        }
    }

    // Clean up and close
    printf("END string entered, closing process initialized\n");
    dico = dico_delete(dico);
    if (dico != NULL) {
        ERR("Dico delete failed");
        fclose(fp);
        return -5;
    }

    fclose(fp);
    printf("FIN\n");
    return 0;  // Success
}
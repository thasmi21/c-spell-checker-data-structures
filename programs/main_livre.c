#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dico_utils.h"

#define ERR(msg) fprintf(stderr, "Error in main.c: %s\n", msg)

int lecture(FILE* fp, char* mot) {
    char inter[512];  // Tableau pour stocker le mot extrait
    int j = 0, c;

    // Lire chaque caractère jusqu'à la fin du mot
    do {
        c = fgetc(fp);  // Lire le caractère suivant
        if (c == EOF) return 0;  // Fin du fichier
        if (j >= 511) return 0;  // Si le mot est trop long, retour

        // Ignorer les apostrophes et les traits d'union, les considérer comme des séparateurs
        if (c == '\'' || c == '-') {
            if (j > 0) {
                inter[j] = '\0';  // Terminer la chaîne et renvoyer le mot extrait
                strcpy(mot, inter);  // Copier le mot dans mot
                return 1;  // Mot trouvé, retour
            }
        }
        // Convertir en minuscule et ajouter les caractères non blancs/ponctuations
        if (!isspace(c) && !ispunct(c)) {
            inter[j++] = tolower(c);  // Convertir en minuscule et ajouter
        }
        // Gérer les espaces (fin d'un mot)
        else if (isspace(c)) {
            if (j > 0) {
                inter[j] = '\0';  // Terminer la chaîne
                strcpy(mot, inter);  // Copier dans le mot
                return 1;  // Mot trouvé
            }
        }
        else {
            // Ignorer toutes les autres ponctuations
            continue;
        }
    } while (1);

    return 0;  // Aucun mot trouvé
}

int main(int argc, char* argv[]) {

    // Ensure correct number of arguments
    if (argc != 4) {
        ERR("Usage: ./dico dico.txt -a|-h|-tt|-tp|-ttc|ttp (choose one option) book.txt");
        return -1;
    }

    // Open the dictionary file
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        ERR("Failed to open the dictionary file");
        return -2;
    }

    FILE* fp_book = fopen(argv[3], "r");
    if (fp == NULL) {
        ERR("Failed to open the book file");
        return -3;
    }

    FILE* fp_error = fopen("result.txt", "w");
    if (fp == NULL) {
        ERR("Failed to write the book file");
        return -4;
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
    while (lecture(fp_book, buffer) == 1) {
        
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        if (strcmp(buffer, "FIN") == 0) {
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
            fprintf(fp_error, "%s\n", buffer);  // "%s" permet d'écrire une chaîne

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
    fclose(fp_book);
    fclose(fp_error);
    printf("FIN\n");
    return 0;  // Success
}
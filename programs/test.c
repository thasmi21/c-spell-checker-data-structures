#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lecture(FILE* fp, char* mot) {
    char inter[512];
    int j, c;
    j = 0;

    do {
        c = fgetc(fp);
        if (c == EOF) return 0;  // Fin du fichier

        // Vérifier si le mot dépasse 512 caractères
        if (j >= 511) {
            // Ne pas ajouter plus de caractères si la taille limite est atteinte
            return 0;  // Retourner 0 pour signaler que le mot est trop long
        }

        if (isspace(c) || ispunct(c)) {
            if (j > 0) {  // Si un mot a été formé
                inter[j] = '\0';  // Terminer le mot
                strcpy(mot, inter);  // Copier dans le mot
                return 1;  // Retourner 1 pour indiquer qu'un mot a été trouvé
            }
        } else {
            inter[j++] = c;  // Ajouter le caractère au mot
        }
    } while (1);

    return 0;  // Si le fichier se termine sans avoir trouvé de mot
}

int main() {
    FILE *fp = fopen("./../livre_txt/a_la_recherche_du_temps_perdu.txt", "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return 1;
    }

    char mot[512];  // Buffer pour le mot extrait
    while (lecture(fp, mot)) {
        printf("%s\n", mot);  // Afficher chaque mot extrait
    }

    fclose(fp);
    return 0;
}

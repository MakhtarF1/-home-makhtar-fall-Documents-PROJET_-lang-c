#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MATRICULE 20
#define MAX_NOM 50

void marquer_present(const char *matricule) {
    FILE *fichier;
    FILE *temp;
    fichier = fopen("marquer.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fichier == NULL || temp == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char nom[MAX_NOM];
        char present[10];

        if (sscanf(ligne, "%s %s", nom, present) == 2) {
            if (strcmp(nom, matricule) == 0) {
                fprintf(temp, "%s 1\n", matricule);
            } else {
                fprintf(temp, "%s", ligne);
            }
        }
    }

    fprintf(temp, "%s present\n", matricule);

    fclose(fichier);
    fclose(temp);

    remove("marquer.txt");
    rename("temp.txt", "marquer.txt");

    printf("%s a été marqué comme présent.\n", matricule);
}

int verifier_matricule(const char *matricule) {
    FILE *fichier;
    fichier = fopen("marquer.txt", "r");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        char nom[MAX_NOM];

        if (sscanf(ligne, "%s", nom) == 1) {
            if (strcmp(nom, matricule) == 0) {
                fclose(fichier);
                return 1;
            }
        }
    }

    fclose(fichier);
    return 0;
}

void saisir_matricule() {
    char matricule[MAX_MATRICULE];

    while (1) {
        printf("Veuillez saisir votre matricule (ex: MAT-001 MAKHTAR) : ");
        fgets(matricule, sizeof(matricule), stdin);

        // Supprimer le '\n' de fin de ligne de la saisie
        matricule[strcspn(matricule, "\n")] = 0;

        // Vérifier si l'utilisateur a saisi directement "entrer"
        if (strcmp(matricule, "entrer") == 0) {
            printf("Erreur : Veuillez saisir un matricule valide.\n");
            continue;
        }

        break;
    }

    if (verifier_matricule(matricule)) {
        printf("Matricule trouvé.\n");
        marquer_present(matricule);
    } else {
        printf("Matricule non trouvé.\n");
    }
}

int main() {
    saisir_matricule();

    return 0;
}

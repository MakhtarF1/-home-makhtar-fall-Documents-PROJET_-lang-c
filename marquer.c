#include <stdio.h>
#include <string.h>
#include <time.h>

void marquer_present(const char *matricule) {
    FILE *fichier;
    fichier = fopen("marquer.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    time_t temps_actuel;
    struct tm *temps_info;
    char date_format[20];

    time(&temps_actuel);
    temps_info = localtime(&temps_actuel);

    strftime(date_format, sizeof(date_format), "%d/%m/%Y", temps_info);

    fprintf(fichier, "%s - Présent le %s\n", matricule, date_format);
    printf("%s a été marqué comme présent le %s.\n", matricule, date_format);

    fclose(fichier);
}

int main() {
    char matricule[20];

    printf("Veuillez saisir votre matricule (ex: MAT-001 MAKHTAR) : ");
    fgets(matricule, sizeof(matricule), stdin);

    // Supprimer le '\n' de fin de ligne de la saisie
    matricule[strcspn(matricule, "\n")] = 0;

    marquer_present(matricule);

    return 0;
}

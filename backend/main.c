#include "processing.h"



int main(void) {
    Mesure *mesures = NULL;
    int nb_mesures = 0;
    int capacite = 0;
    int choix = -1;

    while (choix != 0) {
        afficher_menu();
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n'); // Purge du tampon
            continue;
        }

        switch (choix) {
            case 1: {
                if (mesures != NULL) free(mesures);
                mesures = charger_fichier_csv("measures_in.csv", &nb_mesures, &capacite);
                break;
            }
            case 2:
                afficher_mesures(mesures, nb_mesures);
                break;

            
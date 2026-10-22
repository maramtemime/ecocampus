// We include this file so we can use our structures and functions.
#include "processing.h"

// This function shows the choices the user can select from.
void afficher_menu()
{
    printf("\n============================================\n");
    printf("         ECOCAMPUS - MODULE C (v1.0)        \n");
    printf("============================================\n");
    printf("1. Charger les mesures depuis measures_in.csv\n");
    printf("2. Afficher toutes les mesures\n");
    printf("3. Ajouter une mesure\n");
    printf("4. Supprimer une mesure\n");
    printf("5. Rechercher des mesures (Batiment / Ressource)\n");
    printf("6. Trier les mesures (Consommation / Date)\n");
    printf("7. Calculer & Afficher les Statistiques\n");
    printf("8. Calculer la Moyenne Mobile (Bonus)\n");
    printf("9. Exporter les donnees dans data.json\n");
    printf("0. Quitter\n");
    printf("============================================\n");
    printf("Choix : ");
}

// The program starts here. This function controls the menu and the user choices.
int main(void)
{
    // This pointer will point to the list of measurements. At the beginning, the list is empty.
    Mesure *mesures = NULL;
    // Number of measurements currently saved in the list.
    int nb_mesures = 0;
    // Number of measurements that can fit in the memory we reserved.
    int capacite = 0;
    int choix = -1;

    // Keep showing the menu until the user chooses 0.
    while (choix != 0)
    {
        afficher_menu();
        if (scanf("%d", &choix) != 1)
        {
            while (getchar() != '\n')
                ; // Purge du tampon
            continue;
        }

        // Run the correct action depending on the number entered by the user.
        switch (choix)
        {
        // Choice 1: load measurements from the CSV file.
        case 1:
        {
            if (mesures != NULL)
                free(mesures);
            mesures = charger_fichier_csv("measures_in.csv", &nb_mesures, &capacite);
            break;
        }
        // Choice 2: display all measurements currently in memory.
        case 2:
            afficher_mesures(mesures, nb_mesures);
            break;

        // Choice 3: ask the user for a new measurement and add it to the list.
        case 3:
        {
            Mesure m;
            printf("Batiment (ex: ISET_Bizerte, ENIB) : ");
            scanf("%49s", m.batiment);
            printf("Ressource (electricite/eau/chauffage) : ");
            scanf("%19s", m.ressource);
            printf("Valeur consommee : ");
            scanf("%f", &m.valeur);
            printf("Seuil d'alerte : ");
            scanf("%f", &m.seuil);
            printf("Date (ex: 2026-03-30 10:00) : ");
            scanf(" %[^\n]", m.date);

            ajouter_mesure(&mesures, &nb_mesures, &capacite, m);
            break;
        }
        // Choice 4: display the list, then ask which measurement to delete.
        case 4:
        {
            int index;
            afficher_mesures(mesures, nb_mesures);
            printf("Entrez l'index (ID) a supprimer : ");
            scanf("%d", &index);
            supprimer_mesure(mesures, &nb_mesures, index);
            break;
        }
        // Choice 5: search measurements by building name or resource type.
        case 5:
        {
            int sous_choix;
            printf("1. Rechercher par Batiment\n2. Rechercher par Ressource\nChoix : ");
            scanf("%d", &sous_choix);
            if (sous_choix == 1)
            {
                char bat[50];
                printf("Nom du batiment : ");
                scanf("%49s", bat);
                rechercher_par_batiment(mesures, nb_mesures, bat);
            }
            else if (sous_choix == 2)
            {
                char res[20];
                printf("Type de ressource : ");
                scanf("%19s", res);
                rechercher_par_ressource(mesures, nb_mesures, res);
            }
            break;
        }
        // Choice 6: sort measurements by consumption or by date.
        case 6:
        {
            int sous_choix;
            printf("1. Tri par consommation (Croissant)\n");
            printf("2. Tri par consommation (Decroissant)\n");
            printf("3. Tri par date\nChoix : ");
            scanf("%d", &sous_choix);
            if (sous_choix == 1)
                trier_par_consommation(mesures, nb_mesures, 1);
            else if (sous_choix == 2)
                trier_par_consommation(mesures, nb_mesures, 0);
            else if (sous_choix == 3)
                trier_par_date(mesures, nb_mesures);
            break;
        }
        // Choice 7: calculate and display statistics for each building.
        case 7:
        {
            int nb_stats = 0;
            Statistique *stats = calculer_statistiques(mesures, nb_mesures, &nb_stats);
            afficher_statistiques(stats, nb_stats);
            if (stats)
                free(stats);
            break;
        }
        // Choice 8: calculate the moving average for one building.
        case 8:
        {
            char bat[50];
            int fenetre;
            printf("Nom du batiment : ");
            scanf("%49s", bat);
            printf("Taille de la fenetre (ex: 3 pour les 3 dernieres mesures) : ");
            scanf("%d", &fenetre);
            float mm = calculer_moyenne_mobile(mesures, nb_mesures, bat, fenetre);
            printf("Moyenne mobile (%d dernieres valeurs) pour %s = %.2f\n", fenetre, bat, mm);
            break;
        }
        // Choice 9: save the measurements and statistics in a JSON file.
        case 9:
            exporter_json("data.json", mesures, nb_mesures);
            break;

        // Choice 0: stop the program.
        case 0:
            printf("Fermeture du programme.\n");
            break;

        default:
            printf("Choix invalide.\n");
        }
    }

    // Free the list from memory before the program finishes.
    if (mesures != NULL)
    {
        free(mesures);
    }

    return 0;
}
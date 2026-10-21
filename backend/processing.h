#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representant une mesure energetique
typedef struct {
    char batiment[50];   // Nom du batiment (ex: ISET_Bizerte, ENIB, ISG, Foyer)
    char ressource[20];  // Type de ressource: electricite, eau, chauffage
    float valeur;        // Valeur consommee
    float seuil;         // Seuil limite a ne pas depasser
    char date[20];       // Date et heure (ex: 2026-03-30 08:00)
    int alerte;          // 1 si valeur > seuil, 0 sinon
} Mesure;

// Structure representant les statistiques calculees par batiment
typedef struct {
    char batiment[50];
    float total;
    float moyenne;
    float min;
    float max;
    int nb_alertes;
} Statistique;

// --- Prototypes des fonctions ---

// Chargement & Sauvegarde
Mesure* charger_fichier_csv(const char *nom_fichier, int *nb_mesures, int *capacite);
void exporter_json(const char *nom_fichier, const Mesure *tableau, int nb_mesures);

// Gestion du tableau dynamique
int ajouter_mesure(Mesure **tableau, int *nb_mesures, int *capacite, Mesure nouvelle);
int supprimer_mesure(Mesure *tableau, int *nb_mesures, int index);

// Recherche & Tri
void rechercher_par_batiment(const Mesure *tableau, int nb_mesures, const char *batiment);
void rechercher_par_ressource(const Mesure *tableau, int nb_mesures, const char *ressource);
void trier_par_consommation(Mesure *tableau, int nb_mesures, int croissant);
void trier_par_date(Mesure *tableau, int nb_mesures);

// Analyse & Statistiques
void detecter_anomalies(Mesure *tableau, int nb_mesures);
Statistique* calculer_statistiques(const Mesure *tableau, int nb_mesures, int *nb_stats);
float calculer_moyenne_mobile(const Mesure *tableau, int nb_mesures, const char *batiment, int fenetre);

// Affichage Console
void afficher_mesures(const Mesure *tableau, int nb_mesures);
void afficher_statistiques(const Statistique *stats, int nb_stats);

#endif // PROCESSING_H
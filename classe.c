#include "classe.h"
// Fonction pour initialiser une liste d'ID
ListeID *initListeID() {
    return NULL;
}

// Fonction pour ajouter un ID à une liste d'ID
ListeID *ajouterID(ListeID *liste, int ID, int temps) {
    ListeID *nouveau = malloc(sizeof(ListeID));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    nouveau->ID = ID;
    nouveau->temps = temps;
    nouveau->suivant = NULL;
    if (liste == NULL) {
        return nouveau;
    } else {
        ListeID *temp = liste;
        while (temp->suivant != NULL) {
            temp = temp->suivant;
        }
        temp->suivant = nouveau;
        return liste;
    }
}
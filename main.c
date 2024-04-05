#include <stdio.h>
#include <stdlib.h>
#include "classe.h"
int main() {
    // Exemple d'utilisation des structures de données

    // Initialisation d'une donnée
    Donnee donnee1 = {1, 100};

    // Initialisation d'une liste d'ID
    ListeID *listedata = initListeID();
    listedata = ajouterID(listedata, 1,0);
    listedata = ajouterID(listedata, 2,0);
    listedata = ajouterID(listedata, 3,0);

    // Initialisation d'un utilisateur
    Utilisateur utilisateur1 = {1, listedata, 1};

    // Initialisation d'un nœud système
    NoeudSysteme noeud1 = {1, 1000, NULL, NULL};
    return 0;
}
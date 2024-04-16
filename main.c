#include <stdio.h>
#include <stdlib.h>
#include "classe.h"
int main() {
    // Exemple d'utilisation des structures de données
    // init de l'exemple utilisé dans l'énoncé
    // Initialisation d'une donnée
    Environnement *env = initListeENV();
    Donnee donnee0 = {0, 40};
    Donnee donnee1 = {1, 25};
    Donnee donnee2 = {2, 25};
    env = agrandir_env(env, &donnee0, NULL, NULL);
    env = agrandir_env(env, &donnee1, NULL, NULL);
    env = agrandir_env(env, &donnee2, NULL, NULL);
    // Initialisation d'une liste d'ID
    ListeID *listedata = initListeID();
    listedata = ajouterID(listedata, 0,0);
    listedata = ajouterID(listedata, 1,0);
    listedata = ajouterID(listedata, 2,0);

    // Initialisation d'un utilisateur
    Utilisateur utilisateur1 = {1001, listedata, 2001};
    env = agrandir_env(env, NULL, NULL, &utilisateur1);
    // Initialisation d'un nœud système
    ListeID *liste_acces1 = initListeID();
    ListeID *liste_acces2 = initListeID();
    ListeID *liste_acces3 = initListeID();
    ListeID *liste_data1 = initListeID();
    ListeID *liste_data2 = initListeID();
    ListeID *liste_data3 = initListeID();
    liste_acces1 = ajouterID(liste_acces1, 1001, 2);
    liste_acces1 = ajouterID(liste_acces1, 2002, 1);
    liste_acces2 = ajouterID(liste_acces2, 2001, 1);
    liste_acces2 = ajouterID(liste_acces2, 2003, 1);
    liste_acces3 = ajouterID(liste_acces3, 2002, 1);
    NoeudSysteme noeud1 = {2001, 50, NULL, liste_acces1};
    NoeudSysteme noeud2 = {2002, 40, NULL, liste_acces2};
    NoeudSysteme noeud3 = {2003, 40, NULL, liste_acces3};
    env = agrandir_env(env, NULL, &noeud1, NULL);
    env = agrandir_env(env, NULL, &noeud2, NULL);
    env = agrandir_env(env, NULL, &noeud3, NULL);
    inserer_donnee(env);
    printf("%d\n", capacite_restant(&noeud1, env));
    printf("%d\n", capacite_restant(&noeud2, env));
    printf("%d\n", capacite_restant(&noeud3, env));
    return 0;
}